#include <iostream>
#include <memory>
#include <QUrl>
#include <QCoreApplication>
#include <QString>
#include <QVector>

#include "user.h"
#include "parent.h"
#include "bnbclient.h"

using namespace std;

int main(int argc, char * * argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("bread-n-butter-common");
    QCoreApplication::setApplicationVersion("0.1");

    BNBClient c(QUrl("http://localhost:1312"));

    QObject::connect(&c, &BNBClient::getParentsFailed, [] (QString s) {
        cout << s.toStdString() << endl;
    });

    QObject::connect(&c, &BNBClient::getParentsSucceeded, [] (QVector<shared_ptr<Parent>> ps) {
        for (shared_ptr<Parent> p : ps)
        {
            cout << p->getName().toStdString() << endl;
        }
    });

    c.getParents();

    QObject::connect(&c, &BNBClient::postParentFailed, [] (QString s) {
        cout << s.toStdString() << endl;
    });

    QObject::connect(&c, &BNBClient::postParentSucceeded, [] (const shared_ptr<Parent> p) {
        cout << p->getName().toStdString() << endl;
    });

    User u;
    u.setUsername("squonch2020");
    u.setPassword("i_4m_da_$q0nch");

    Parent p;
    p.setUser(u);
    p.setName("Squonch");

    c.postParent(p);

    QCoreApplication::exec();

    return 0;
}
