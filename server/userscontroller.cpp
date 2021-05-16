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

    string uTypeStr = session->
            get_request()->
            get_path_parameter(TYPE);

    UserType uType = User::getType(QString::fromStdString(uTypeStr));

    BNBResponse res;
    int statusCode = restbed::OK;

    QJsonArray users;
    if (uType == PARENT)
    {
        db->foreachParent([&](Parent & p) {
                QJsonObject o;
                p.toJson(o);
                users.append(o);
            });
        res.setResult(users);
    }
    else if (uType == SHELTER_OWNER)
    {
        db->foreachShelterOwner([&](ShelterOwner & so) {
                QJsonObject o;
                so.toJson(o);
                users.append(o);
            });
        res.setResult(users);
    }
    else if (uType == ADMINISTRATOR)
    {
        db->foreachAdmin([&](Administrator & a) {
                QJsonObject o;
                a.toJson(o);
                users.append(o);
            });
        res.setResult(users);
    }
    else
    {
        res.setError("Invalid user-type");
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
}

void UsersController::postHandler(const shared_ptr<Session> session)
{
    Db * db = Db::instance();

    size_t contentLen = session->get_request()->
            get_header("Content-Length", 0);

    session->fetch(contentLen, [&](const shared_ptr<Session> session, const Bytes & body)
    {
        QByteArray reqBytes((char *) body.data(), body.size());

        QJsonParseError parseError;
        QJsonDocument reqBody = QJsonDocument::fromJson(reqBytes, &parseError);

        BNBResponse res;
        int statusCode = restbed::INTERNAL_SERVER_ERROR;
        if (reqBody.isObject())
        {
            BNBRequest req;

            string uTypePathStr = session->get_request()->
                        get_path_parameter(TYPE);
            req.setType(QString::fromStdString(uTypePathStr));

            req.fromJson(reqBody.object());

            BNBModel * model = nullptr;
            UserType uType = User::getType(req.getType());

            QDateTime now = QDateTime::currentDateTimeUtc();
            if (uType == PARENT)
            {
                Parent * p = new Parent();
                p->fromJson(req.getPayload().toObject());
                p->getUser().setCreatedAt(now);
                model = p;
            }
            else if (uType == SHELTER_OWNER){
                ShelterOwner * so = new ShelterOwner();
                so->fromJson(req.getPayload().toObject());
                so->getUser().setCreatedAt(now);
                model = so;
            }
            else if (uType == ADMINISTRATOR){
                Administrator * a = new Administrator();
                a->fromJson(req.getPayload().toObject());
                a->getUser().setCreatedAt(now);
                model = a;
            }
            else
            {
                res.setError("Invalid user-type");
                statusCode = restbed::BAD_REQUEST;
            }

            QString validErr;
            if (model != nullptr)
                validErr = model->validation();

            if (model == nullptr)
            {
                if (!validErr.isEmpty())
                {
                    res.setError(validErr);
                    statusCode = restbed::BAD_REQUEST;
                }
            }
            else
            {
                QString dbErr;
                if (uType == PARENT)
                {
                    db->createParentAndUser(* (Parent *) model, &dbErr);
                }
                else if (uType == SHELTER_OWNER)
                {
                    db->createShelterOwnerAndUser(* (ShelterOwner *) model, &dbErr);
                }
                else if (uType == ADMINISTRATOR)
                {
                    db->createAdministratorAndUser(* (Administrator *) model, &dbErr);
                }

                if (dbErr.isEmpty())
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
