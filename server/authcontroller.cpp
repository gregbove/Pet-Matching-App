#include "authcontroller.h"

void AuthController::addToResource(const shared_ptr<Resource> res)
{
    set<string> pathList = {
        (baseUrl + "/").toStdString()
    };

    res->set_paths(pathList);
    res->set_method_handler("POST", std::bind(
                                    &AuthController::postHandler,
                                    this, std::placeholders::_1));
}

void AuthController::postHandler(const shared_ptr<Session> session)
{
    Db * db = Db::instance();

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

            User * u = new User();
            u->fromJson(req.getPayload().toObject());

            BNBModel * m = nullptr;
            UserType uType;
            QString err;
            if (db->getUser(u->getUsername(), &m, uType, &err))
            {
                if (m != nullptr)
                {
                    User mu;
                    switch (uType) {
                    case PARENT:
                        mu = ((Parent *) m)->getUser();
                        break;
                    case SHELTER_OWNER:
                        mu = ((ShelterOwner *) m)->getUser();
                        break;
                    case ADMINISTRATOR:
                        mu = ((Administrator *) m)->getUser();
                        break;
                    default:
                        break;
                    }

                    if (mu.getPassword() == u->getPassword())
                    {
                        QJsonObject o;
                        m->toJson(o);
                        o[USER_TYPE] = User::getTypeStr(uType);

                        res.setResult(o);
                        statusCode = restbed::OK;
                    }
                    else
                    {
                        res.setError("Invalid username or password");
                        statusCode = restbed::UNAUTHORIZED;
                    }
                }
                else
                {
                    res.setError("Invalid username or password");
                    statusCode = restbed::UNAUTHORIZED;
                }
            }
            else
            {
                res.setError(err);
            }
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
