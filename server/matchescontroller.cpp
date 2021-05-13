#include "matchescontroller.h"

void MatchesController::addToResource(const shared_ptr<Resource> res)
{
    set<string> pathList = {
                (baseUrl + "/{parentId: [0-9]+}").toStdString()
    };

    res->set_paths(pathList);
    res->set_method_handler("GET", std::bind(
                                &MatchesController::getHandler,
                                this, std::placeholders::_1));
    res->set_method_handler("POST", std::bind(
                                &MatchesController::postHandler,
                                this, std::placeholders::_1));
}

void MatchesController::getHandler(const shared_ptr<Session> session)
{
    Db * db = Db::instance();

    string pIdStr = session->
            get_request()->
            get_path_parameter(ID_PATH_PARAM);

    int pId = QString::fromStdString(pIdStr).toInt();

    QJsonArray matches;
    QString err;
    db->foreachPetMatch(pId, [&](PetMatch & p) {
        QJsonObject o;
        p.toJson(o);
        matches.append(o);
    }, &err);

    int statusCode = restbed::OK;
    BNBResponse res;
    if (err.isNull())
    {
        res.setResult(matches);
    }
    else
    {
        res.setError(err);
        statusCode = restbed::INTERNAL_SERVER_ERROR;
    }

    QJsonObject resObj;
    res.toJson(resObj);

    const string resStr = QJsonDocument(resObj).toJson().toStdString();
    session->close(statusCode, resStr, {
                       { "Content-Length", ::to_string(resStr.length()) }
                   });
}

void MatchesController::postHandler(const shared_ptr<Session> session)
{
    using namespace chrono;
    Db * db = Db::instance();

    string pIdStr = session->
            get_request()->
            get_path_parameter(ID_PATH_PARAM);

    int pId = QString::fromStdString(pIdStr).toInt();

    int statusCode = restbed::OK;
    BNBResponse res;
    QString err;

    auto startT = high_resolution_clock::now();
    bool succeeded = db->updatePetMatches(pId, &err);
    auto endT = high_resolution_clock::now();

    if (succeeded)
    {
        auto dur = duration_cast<microseconds>(endT - startT);
        double millis = (double) dur.count() / 1000.;

        res.setResult(QJsonValue::fromVariant(millis));
    }
    else
    {
        res.setError(err);
        statusCode = restbed::INTERNAL_SERVER_ERROR;
    }

    QJsonObject resObj;
    res.toJson(resObj);

    const string resStr = QJsonDocument(resObj).toJson().toStdString();
    session->close(statusCode, resStr, {
                       { "Content-Length", ::to_string(resStr.length()) }
                   });
}
