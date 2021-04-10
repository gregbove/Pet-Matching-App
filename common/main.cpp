#include <iostream>
#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>

#include "user.h"

using namespace std;

int main()
{
    User * user1 = new User();

    cout << user1->isValid() << endl;
    cout << user1->validation().toStdString() << endl;

    user1->setUsername("Womp");
    user1->setPassword("thwompthwomp");

    QJsonObject * userJson1 = new QJsonObject();
    user1->toJson(* userJson1);

    User * user2 = new User();
    user2->fromJson(* userJson1);

    QJsonObject * userJson2 = new QJsonObject();
    user2->toJson(* userJson2);

    QJsonDocument * doc1 = new QJsonDocument(* userJson1);
    QJsonDocument * doc2 = new QJsonDocument(* userJson2);

    cout << doc1->toJson().toStdString() << endl;
    cout << doc2->toJson().toStdString() << endl;

    return 0;
}
