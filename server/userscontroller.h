#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H

#include "bnbcontroller.h"
#include "../common/bnbresponse.h"

#include <memory>
#include <restbed>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

using namespace std;
using namespace restbed;

class UsersController : public BNBController
{
public:
    UsersController(QString baseUrl = "/users") : BNBController(baseUrl) {};

    void addToResource(const shared_ptr<Resource>);

protected:
    void getIndexHandler(const shared_ptr<Session> session);

};

#endif // USERSCONTROLLER_H
