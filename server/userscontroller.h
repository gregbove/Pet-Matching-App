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

/**
 * @brief Handles fetching and creating different types of Users
 *
 * Endpoints:
 * /users/{type: parent|owner|admin}
 * /users/{id: a postivive integer}
 *
 * > GET /users/parents
 * < a BNBResponse containing a list of Parents
 *
 * > POST /users/parent
 * | a BNBRequest containing a parent to be created
 * < a BNBResponse containing the newly created parent or an error
 */
class UsersController : public BNBController
{
public:
    UsersController(QString baseUrl = "/users") : BNBController(baseUrl) {};

    void addToResource(const shared_ptr<Resource>);

protected:
    static constexpr const char* TYPE = "type";
    static constexpr const char* ID = "id";

    void getHandler(const shared_ptr<Session> session);
    void postHandler(const shared_ptr<Session> session);

};

#endif // USERSCONTROLLER_H
