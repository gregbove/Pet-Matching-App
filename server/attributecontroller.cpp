#include "attributecontroller.h"



void AttributeController::addToResource(const shared_ptr<Resource> res)
{
    set<string> pathList = {
        (baseUrl + "/").toStdString()
    };

    res->set_paths(pathList);
    res->set_method_handler("GET", std::bind(
                                &AttributeController::getHandler,
                                this, std::placeholders::_1));
    res->set_method_handler("POST", std::bind(
                                &AttributeController::postHandler,
                                this, std::placeholders::_1));
}

void AttributeController::getHandler(const shared_ptr<Session> session)
{
    Db * db = Db::instance();

    QJsonArray attributes;
    //    db->foreachAttribute([&attributes](Attribute & attr) {
    //        QJsonObject o;
    //        attr.toJson(o);
    //        attributes.append(o);
    //    });
    //    Waiting for the corresponding db function


    BNBResponse res;
    res.setResult(attributes);

    QJsonObject resObj;
    res.toJson(resObj);

    const string resStr = QJsonDocument(resObj).toJson().toStdString();
    session->close(restbed::OK, resStr, {
                       { "Content-Type", "application/json" },
                       { "Content-Length", ::to_string(resStr.length()) },
                       { "Connection", "close" }
                   });
}

void AttributeController::postHandler(const shared_ptr<Session> session)
{
    Db * db = Db::instance();

    size_t contentLen = session->get_request()->get_header("Content-Length", 0);

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
            req.fromJson(reqBody.object());

            BNBModel * model = nullptr;

            Attribute* attr = new Attribute();
            attr->fromJson(req.getPayload().toObject());
            model = attr;


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
//                if (db->createAttribute(* (Attribute *) model, &dbErr))
//                {
//                    QJsonObject mObj;
//                    model->toJson(mObj);
//                    res.setResult(mObj);
//                    statusCode = restbed::CREATED;
//                }
//                else
//                {
//                    res.setError(dbErr);
//                    statusCode = restbed::INTERNAL_SERVER_ERROR;
//                }

//      Wait for the corresponding db function

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
