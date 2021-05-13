#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include "../common/bnbresponse.h"
#include "../common/bnbrequest.h"
#include "../common/bnbmodel.h"
#include "../common/user.h"

#include "bnbcontroller.h"
#include "db.h"

#include <memory>
#include <restbed>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

using namespace std;
using namespace restbed;

class AuthController : public BNBController
{
public:
    AuthController(QString baseUrl = "/login") : BNBController(baseUrl) {};

    void addToResource(const shared_ptr<Resource>);

protected:
    static constexpr const char* USER_TYPE = "userType";

    void postHandler(const shared_ptr<Session> session);

};

#endif // AUTHCONTROLLER_H
