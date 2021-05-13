#include "userscontroller.h"

void UsersController::addToResource(const shared_ptr<Resource> res)
{
    set<string> pathList = {
//        (baseUrl + "/").toStdString(),
        (baseUrl + "/{type: [a-z]+}").toStdString(),
        (baseUrl + "/{id: [0-9]+}").toStdString()
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
    Db * db = Db::instance();

    QJsonArray parents;
    QJsonArray shelterOwners;
    QJsonArray admins;
    db->foreachParent([&parents](Parent & p) {
        QJsonObject o;
        p.toJson(o);
        parents.append(o);
    });

    db->foreachShelterOwner([&shelterOwners](ShelterOwner & so) {
        QJsonObject o;
        so.toJson(o);
        shelterOwners.append(o);
    });

    db->foreachAdmin([&admins](Administrator & a) {
        QJsonObject o;
        a.toJson(o);
        admins.append(o);
    });

    BNBResponse res;
    res.setResult(parents);

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
    Db * db = Db::instance();

    size_t contentLen = session->get_request()->get_header("Content-Length", 0);
    string modelType = session->get_request()->get_path_parameter(TYPE);

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
            req.setType(QString::fromStdString(modelType));
            req.fromJson(reqBody.object());

            BNBModel * model = nullptr;
            QString type = req.getType();
            QDateTime now = QDateTime::currentDateTimeUtc();
            if (type.startsWith("parent"))
            {
                Parent * p = new Parent();
                p->fromJson(req.getPayload().toObject());
                p->getUser().setCreatedAt(now);
                model = p;
            }
            else if (type.startsWith("shelterowner")){
                ShelterOwner * so = new ShelterOwner();
                so->fromJson(req.getPayload().toObject());
                so->getUser().setCreatedAt(now);
                model = so;
            }
            else if (type.startsWith("administrator")){
                Administrator * a = new Administrator();
                a->fromJson(req.getPayload().toObject());
                a->getUser().setCreatedAt(now);
                model = a;
            }
            else
            {
                res.setError("Invalid type");
                statusCode = restbed::BAD_REQUEST;
            }

            QString validErr;
            if (model != nullptr)
                validErr = model->validation();

            if (!validErr.isEmpty())
            {
                res.setError(validErr);
                statusCode = restbed::BAD_REQUEST;
            }
            else
            {
                QString dbErr;
                if (db->createParentAndUser(* (Parent *) model, &dbErr))
                {
                    QJsonObject mObj;
                    model->toJson(mObj);
                    res.setResult(mObj);
                    statusCode = restbed::CREATED;
                }
                else if (db->createShelterOwnerAndUser(* (ShelterOwner *) model, &dbErr))
                {
                    QJsonObject mObj;
                    model->toJson(mObj);
                    res.setResult(mObj);
                    statusCode = restbed::CREATED;
                }
                else if (db->createAdministratorAndUser(* (Administrator *) model, &dbErr))
                {
                    QJsonObject mObj;
                    model->toJson(mObj);
                    res.setResult(mObj);
                    statusCode = restbed::CREATED;
                }
                else
                {
                    res.setError(dbErr);
                    statusCode = restbed::INTERNAL_SERVER_ERROR;
                }

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
