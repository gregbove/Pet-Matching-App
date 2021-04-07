#include "defaultcontroller.h"

DefaultController::DefaultController(string baseUrl)
{
    this->baseUrl = baseUrl;
}

shared_ptr<Resource> DefaultController::getResource()
{
    set<string> pathList = set<string>({
                                           baseUrl + "/"
                                       });

    shared_ptr<Resource> resource = make_shared<Resource>();
    resource->set_paths(pathList);
    resource->set_method_handler("GET", std::bind(
                                     &DefaultController::getIndexHandler,
                                     this, std::placeholders::_1));

    return resource;
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
