#include <memory>
#include <restbed>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QString>

#include "defaultcontroller.h"
#include "userscontroller.h"
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

    auto settings = make_shared<Settings>();
    settings->set_port(port);
    settings->set_default_header("Connection", "close");

    Service service;
    service.publish(resDefault);
    service.publish(resUsers);

    service.start(settings);

    return EXIT_SUCCESS;
}
