#include <memory>
#include <restbed>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QString>

#include "defaultcontroller.h"
#include "userscontroller.h"
#include "authcontroller.h"
#include "matchescontroller.h"
#include "db.h"

using namespace std;
using namespace restbed;

QString g_config_dbPath;

int main(int argc, char * * argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("bread-n-butter-server");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Bread-N-Butter server application");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption portOption(
                QStringList() << "p" << "port",
                QCoreApplication::translate("main", "Listen on <port>"),
                QCoreApplication::translate("main", "port"));
    parser.addOption(portOption);

    QCommandLineOption dbPathOption(
                QStringList() << "d" << "db-path",
                QCoreApplication::translate("main", "Store the DB at <path>"),
                QCoreApplication::translate("main", "path"));
    parser.addOption(dbPathOption);

    parser.process(app);

    bool noPort = false;
    int port = parser.value(portOption).toInt(& noPort);
    if (noPort || !parser.isSet(portOption))
        port = 1312;

    Db * db = Db::instance();
    if (parser.isSet(dbPathOption))
    {
        db->initialize(parser.value(dbPathOption));
    }
    else
    {
        db->initialize(QCoreApplication::applicationDirPath() + "/bnb.sqlite");
    }

    shared_ptr<DefaultController> ctlDefault = make_shared<DefaultController>();
    const shared_ptr<Resource> resDefault = make_shared<Resource>();
    ctlDefault->addToResource(resDefault);

    shared_ptr<UsersController> ctlUsers = make_shared<UsersController>();
    const shared_ptr<Resource> resUsers = make_shared<Resource>();
    ctlUsers->addToResource(resUsers);

    shared_ptr<AuthController> ctlAuth = make_shared<AuthController>();
    const shared_ptr<Resource> resAuth = make_shared<Resource>();
    ctlAuth->addToResource(resAuth);

    shared_ptr<MatchesController> ctlMatch = make_shared<MatchesController>();
    const shared_ptr<Resource> resMatch = make_shared<Resource>();
    ctlMatch->addToResource(resMatch);

    auto settings = make_shared<Settings>();
    settings->set_port(port);
    settings->set_default_header("Connection", "close");
    settings->set_default_header("Content-Type", "application/json");

    Service service;
    service.publish(resDefault);
    service.publish(resUsers);
    service.publish(resAuth);
    service.publish(resMatch);

    service.start(settings);

    return EXIT_SUCCESS;
}
