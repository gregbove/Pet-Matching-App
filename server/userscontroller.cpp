#include "userscontroller.h"

void UsersController::addToResource(const shared_ptr<Resource> res)
{
    set<string> pathList = {
        (baseUrl + "/").toStdString()
    };

    res->set_paths(pathList);
    res->set_method_handler("GET", std::bind(
                                &UsersController::getIndexHandler,
                                this, std::placeholders::_1));
}

void UsersController::getIndexHandler(const shared_ptr<Session> session)
{
    const QJsonObject user1
    {
        { "username", "bonk" },
        { "password", "hunter2" }
    };

    QJsonArray users = {
        QJsonObject {
            { "username", "bonk" },
            { "password", "hunter2" }
        },
        QJsonObject {
            { "username", "squee" },
            { "password", "pizza_party_2010" }
        }
    };

    BNBResponse res;
    res.setResult(users);

    QJsonObject resObj;
    res.toJson(resObj);

    const string resStr = QJsonDocument(resObj).toJson().toStdString();
    session->close(restbed::OK, resStr, {
                       { "Content-Type", "application/json" },
                       { "Content-Length", ::to_string(resStr.length()) },
                       { "Connection", "close" }
                   });
}
