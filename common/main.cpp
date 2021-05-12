#include <iostream>
#include <memory>
#include <QUrl>
#include <QCoreApplication>
#include <QString>
#include <QVector>

#include "user.h"
#include "shelterowner.h"
#include "bnbclient.h"

using namespace std;

int main(int argc, char * * argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("bread-n-butter-common");
    QCoreApplication::setApplicationVersion("0.1");

    BNBClient c(QUrl("http://localhost:1312"));

    QObject::connect(&c, &BNBClient::postLoginFailed, [] (QString s) {
        cout << s.toStdString() << endl;
    });

    QObject::connect(&c, &BNBClient::postLoginSucceeded, [] (shared_ptr<BNBModel> um, UserType ut) {
        cout << User::getTypeStr(ut).toStdString() << endl;

        if (ut == SHELTER_OWNER)
        {
            auto so = dynamic_pointer_cast<ShelterOwner>(um);
            cout << so->getShelter()->getName().toStdString() << endl;
        }
    });

    User u;
    u.setUsername("sandy");
    u.setPassword("sandy");

    c.postLogin(u);

    QCoreApplication::exec();

    return 0;
}
