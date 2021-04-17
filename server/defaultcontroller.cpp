#include "defaultcontroller.h"

void DefaultController::addToResource(const shared_ptr<Resource> res)
{
    set<string> pathList = {
        (baseUrl + "/").toStdString()
    };

    res->set_paths(pathList);
    res->set_method_handler("GET", std::bind(
                                &DefaultController::getIndexHandler,
                                this, std::placeholders::_1));
}

void DefaultController::getIndexHandler(const shared_ptr<Session> session)
{
    const QJsonObject resObj
    {
        { "message", "Success! Bread-N-Butter is working correctly." }
    };

    const string resStr = QJsonDocument(resObj).toJson().toStdString();
    session->close(OK, resStr, {
                       { "Content-Type", "application/json" },
                       { "Content-Length", ::to_string(resStr.length()) },
                       { "Connection", "close" }
                   });
}
