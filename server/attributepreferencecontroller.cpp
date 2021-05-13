#include "attributepreferencecontroller.h"



void AttributePreferenceController::addToResource(const shared_ptr<Resource> res)
{
    set<string> pathList = {
        (baseUrl + "/{parentId: [0-9]+}").toStdString()
    };

    res->set_paths(pathList);
    res->set_method_handler("GET", std::bind(
                                &AttributePreferenceController::getHandler,
                                this, std::placeholders::_1));
    res->set_method_handler("POST", std::bind(
                                &AttributePreferenceController::postHandler,
                                this, std::placeholders::_1));
}

void AttributePreferenceController::getHandler(const shared_ptr<Session> session)
{
    Db * db = Db::instance();

    QJsonArray attributepre;
    //    db->foreachAttributePreference([&attributes](AttributePreference & attrpre) {
    //        QJsonObject o;
    //        attrpre.toJson(o);
    //        attributepre.append(o);
    //    });
    //    Waiting for the corresponding db function


    BNBResponse res;
    res.setResult(attributepre);

    QJsonObject resObj;
    res.toJson(resObj);

    const string resStr = QJsonDocument(resObj).toJson().toStdString();
    session->close(restbed::OK, resStr, {
                       { "Content-Type", "application/json" },
                       { "Content-Length", ::to_string(resStr.length()) },
                       { "Connection", "close" }
                   });
}

void AttributePreferenceController::postHandler(const shared_ptr<Session> session)
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

            BNBModel * model = nullptr;

            AttributePreference* attrpre = new AttributePreference();
            attrpre->fromJson(req.getPayload().toObject());
            model = attrpre;


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
