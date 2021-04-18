#include "userscontroller.h"

void UsersController::addToResource(const shared_ptr<Resource> res)
{
    set<string> pathList = {
        (baseUrl + "/").toStdString()
    };

    res->set_paths(pathList);
    res->set_method_handler("GET", std::bind(
                                &UsersController::getHandler,
                                this, std::placeholders::_1));
    res->set_method_handler("POST", std::bind(
                                    &UsersController::postHandler,
                                    this, std::placeholders::_1));
}

void UsersController::getHandler(const shared_ptr<Session> session)
{
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

void UsersController::postHandler(const shared_ptr<Session> session)
{
    size_t contentLen = session->get_request()->get_header("Content-Length", 0);

    BNBResponse res;
    int statusCode = restbed::INTERNAL_SERVER_ERROR;

    session->fetch(contentLen, [&](const shared_ptr<Session> session, const Bytes & body)
    {
        QByteArray reqBytes((char *) body.data(), body.size());

        QJsonParseError parseError;
        QJsonDocument reqBody = QJsonDocument::fromJson(reqBytes, &parseError);

        if (reqBody.isObject())
        {
            BNBRequest req;
            req.fromJson(reqBody.object());

            BNBModel * model = nullptr;
            QString type = req.getType();
            QDateTime now = QDateTime::currentDateTimeUtc();
            QString error;
            if (type == "parent")
            {
                Parent * p = new Parent();
                p->fromJson(req.getPayload().toObject());
                p->getUser().setCreatedAt(now);
                model = p;
            }
            else
            {
                error = "Invalid type";
            }

            if (model != nullptr)
                error = model->validation();

            if (error.isEmpty())
            {
                QJsonObject mObj;
                model->toJson(mObj);
                res.setResult(mObj);
                statusCode = restbed::CREATED;
            }
            else
            {
                res.setError(error);
                statusCode = restbed::BAD_REQUEST;
            }

            if (model != nullptr)
                delete model;
        }
        else if (reqBody.isNull())
        {
            res.setError(parseError.errorString());
            statusCode = restbed::BAD_REQUEST;
        }
        else
        {
            res.setError("Request body must be an object");
            statusCode = restbed::BAD_REQUEST;
        }

        QJsonObject resObj;
        res.toJson(resObj);

        const string resStr = QJsonDocument(resObj).toJson().toStdString();

        session->close(statusCode, resStr, {
                           { "Content-Type", "application/json" },
                           { "Content-Length", ::to_string(resStr.length()) },
                           { "Connection", "close" }
                       });
    });
}
