#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H

#include "../common/bnbresponse.h"
#include "../common/bnbrequest.h"
#include "../common/parent.h"

#include "bnbcontroller.h"

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
    void getHandler(const shared_ptr<Session> session);
    void postHandler(const shared_ptr<Session> session);

};

#endif // USERSCONTROLLER_H
