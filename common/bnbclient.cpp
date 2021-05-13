#include "bnbclient.h"

typedef QNetworkReply::NetworkError NetErr;

BNBClient::BNBClient(QUrl baseUrl, QObject *parent) : QObject(parent)
{
    baseUrl.setPath(""); // we expect there to be no path prefix
    base = baseUrl;
}

void BNBClient::getParents()
{
    QUrl pUrl(base); // clone base url
    pUrl.setPath("/users/parents");

    QNetworkRequest req(pUrl);

    QNetworkReply * rep = man.get(req); // queue a GET request

    // when rep::finished gets fired, call this::getParentsFinish
    connect(rep, &QNetworkReply::finished, this, &BNBClient::getParentsFinish);
}

void BNBClient::getAdministrators()
{
    QUrl aUrl(base); // clone base url
    aUrl.setPath("/users/administrators");

    QNetworkRequest req(aUrl);

    QNetworkReply * rep = man.get(req); // queue a GET request

    // when rep::finished gets fired, call this::getAdministratorsFinish
    connect(rep, &QNetworkReply::finished, this, &BNBClient::getAdministratorsFinish);
}

void BNBClient::getShelterOwners()
{
    QUrl sUrl(base); // clone base url
    sUrl.setPath("/users/shelterowners");

    QNetworkRequest req(sUrl);

    QNetworkReply * rep = man.get(req); // queue a GET request

    // when rep::finished gets fired, call this::getShelterOwnersFinish
    connect(rep, &QNetworkReply::finished, this, &BNBClient::getShelterOwnersFinish);
}

void BNBClient::getPets()
{
    QUrl pUrl(base); // clone base url
    pUrl.setPath("/users/pets");

    QNetworkRequest req(pUrl);

    QNetworkReply * rep = man.get(req); // queue a GET request

    // when rep::finished gets fired, call this::getParentsFinish
    connect(rep, &QNetworkReply::finished, this, &BNBClient::getPetsFinish);
}

void BNBClient::postParent(Parent &p)
{
    QUrl pUrl(base); // clone base url
    pUrl.setPath("/users/parents");

    QJsonObject po;
    p.toJson(po); // serialize Parent p

    BNBRequest br;
    br.setPayload(po); // wrap parent in BNBRequest

    QJsonObject ro;
    br.toJson(ro); // serialize BNBRequest br

    QJsonDocument doc;
    doc.setObject(ro); // put serialized br in a document

    QByteArray body = doc.toJson();

    QNetworkRequest req(pUrl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(body.length()));

    QNetworkReply * rep = man.post(req, body); // queue a POST request

    // when rep::finished gets fired, call this::postParentFinish
    connect(rep, &QNetworkReply::finished, this, &BNBClient::postParentFinish);
}

void BNBClient::postAdministrator(Administrator &a)
{
    QUrl pUrl(base); // clone base url
    pUrl.setPath("/users/administrators");

    QJsonObject po;
    a.toJson(po); // serialize Administrator a

    BNBRequest br;
    br.setPayload(po); // wrap parent in BNBRequest

    QJsonObject ro;
    br.toJson(ro); // serialize BNBRequest br

    QJsonDocument doc;
    doc.setObject(ro); // put serialized br in a document

    QByteArray body = doc.toJson();

    QNetworkRequest req(pUrl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(body.length()));

    QNetworkReply * rep = man.post(req, body); // queue a POST request

    // when rep::finished gets fired, call this::postParentFinish
    connect(rep, &QNetworkReply::finished, this, &BNBClient::postAdministratorFinish);
}

void BNBClient::postShelterOwner(ShelterOwner &s)
{
    QUrl pUrl(base); // clone base url
    pUrl.setPath("/users/shelterowners");

    QJsonObject po;
    s.toJson(po); // serialize ShelterOwner s

    BNBRequest br;
    br.setPayload(po); // wrap parent in BNBRequest

    QJsonObject ro;
    br.toJson(ro); // serialize BNBRequest br

    QJsonDocument doc;
    doc.setObject(ro); // put serialized br in a document

    QByteArray body = doc.toJson();

    QNetworkRequest req(pUrl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(body.length()));

    QNetworkReply * rep = man.post(req, body); // queue a POST request

    // when rep::finished gets fired, call this::postParentFinish
    connect(rep, &QNetworkReply::finished, this, &BNBClient::postShelterOwnerFinish);
}

void BNBClient::getPetsFinish()
{
    // get the reply (from getParents) that called us
    QNetworkReply * reply =  (QNetworkReply *) sender();
    BNBResponse * res = parse(reply); // see below

    if (res->getStatus() == OK)
    {
        // result is a JSONArray of JSONObjects of Pet
        QJsonArray arr = res->getResult().toArray();
        QVector<shared_ptr<Pet>> ps;

        for (QJsonValue v : arr)
        {
            shared_ptr<Pet> p = make_shared<Pet>();
            QJsonObject o = v.toObject();
            p->fromJson(o); // deserialize Pet
            ps.append(p);
        }

        getPetsSucceeded(ps); // emit success signal
    }
    else
    {
        getPetsFailed(res->getError()); // emit failure signal
    }
    delete res; // we're done with res, it's contents were parsed
    reply->deleteLater(); // see QNetworkReply best practices
}

void BNBClient::getParentsFinish()
{
    // get the reply (from getParents) that called us
    QNetworkReply * reply =  (QNetworkReply *) sender();
    BNBResponse * res = parse(reply); // see below

    if (res->getStatus() == OK)
    {
        // result is a JSONArray of JSONObjects of Parent
        QJsonArray arr = res->getResult().toArray();
        QVector<shared_ptr<Parent>> ps;

        for (QJsonValue v : arr)
        {
            shared_ptr<Parent> p = make_shared<Parent>();
            QJsonObject o = v.toObject();
            p->fromJson(o); // deserialize Parent
            ps.append(p);
        }
        getParentsSucceeded(ps); // emit success signal
    }
    else
    {
        getParentsFailed(res->getError()); // emit failure signal
    }

    delete res; // we're done with res, it's contents were parsed
    reply->deleteLater(); // see QNetworkReply best practices
}

void BNBClient::getAdministratorsFinish()
{
    // get the reply (from getParents) that called us
    QNetworkReply * reply =  (QNetworkReply *) sender();
    BNBResponse * res = parse(reply); // see below

    if (res->getStatus() == OK)
    {
        // result is a JSONArray of JSONObjects of Administrator
        QJsonArray arr = res->getResult().toArray();
        QVector<shared_ptr<Administrator>> as;

        for (QJsonValue v : arr)
        {
            shared_ptr<Administrator> a = make_shared<Administrator>();
            QJsonObject o = v.toObject();
            a->fromJson(o); // deserialize Administrator
            as.append(a);
        }

        getAdministratorsSucceeded(as); // emit success signal
    }
    else
    {
        getAdministratorsFailed(res->getError()); // emit failure signal
    }

    delete res; // we're done with res, it's contents were parsed
    reply->deleteLater(); // see QNetworkReply best practices
}

void BNBClient::getShelterOwnersFinish()
{
    // get the reply (from getParents) that called us
    QNetworkReply * reply =  (QNetworkReply *) sender();
    BNBResponse * res = parse(reply); // see below

    if (res->getStatus() == OK)
    {
        // result is a JSONArray of JSONObjects of ShelterOwner
        QJsonArray arr = res->getResult().toArray();
        QVector<shared_ptr<ShelterOwner>> ss;

        for (QJsonValue v : arr)
        {
            shared_ptr<ShelterOwner> s = make_shared<ShelterOwner>();
            QJsonObject o = v.toObject();
            s->fromJson(o); // deserialize Parent
            ss.append(s);
        }

        getShelterOwnersSucceeded(ss); // emit success signal
    }
    else
    {
        getShelterOwnersFailed(res->getError()); // emit failure signal
    }

    delete res; // we're done with res, it's contents were parsed
    reply->deleteLater(); // see QNetworkReply best practices
}

void BNBClient::postParentFinish()
{
    // get the reply (from getParents) that called us
    QNetworkReply * reply =  (QNetworkReply *) sender();
    BNBResponse * res = parse(reply); // see below

    if (res->getStatus() == OK)
    {
        const shared_ptr<Parent> p = make_shared<Parent>();
        // result is a JSONObject of a Parent
        QJsonObject o = res->getResult().toObject();
        p->fromJson(o); // deserialize Parent

        postParentSucceeded(p); // emit success signal
    }
    else
    {
        postParentFailed(res->getError()); // emit failure signal
    }

    delete res; // we're done with res, it's contents were parsed
    reply->deleteLater(); // see QNetworkReply best practices
}

void BNBClient::postAdministratorFinish()
{
    // get the reply (from getAdministrators) that called us
    QNetworkReply * reply =  (QNetworkReply *) sender();
    BNBResponse * res = parse(reply); // see below

    if (res->getStatus() == OK)
    {
        const shared_ptr<Administrator> a = make_shared<Administrator>();
        // result is a JSONObject of a Administrator
        QJsonObject o = res->getResult().toObject();
        a->fromJson(o); // deserialize Administrator

        postAdministratorSucceeded(a); // emit success signal
    }
    else
    {
        postAdministratorFailed(res->getError()); // emit failure signal
    }

    delete res; // we're done with res, it's contents were parsed
    reply->deleteLater(); // see QNetworkReply best practices
}

void BNBClient::postShelterOwnerFinish()
{
    // get the reply (from getShelterOwners) that called us
    QNetworkReply * reply =  (QNetworkReply *) sender();
    BNBResponse * res = parse(reply); // see below

    if (res->getStatus() == OK)
    {
        const shared_ptr<ShelterOwner> s = make_shared<ShelterOwner>();
        // result is a JSONObject of a ShelterOwner
        QJsonObject o = res->getResult().toObject();
        s->fromJson(o); // deserialize ShelterOwner

        postShelterOwnerSucceeded(s); // emit success signal
    }
    else
    {
        postShelterOwnerFailed(res->getError()); // emit failure signal
    }

    delete res; // we're done with res, it's contents were parsed
    reply->deleteLater(); // see QNetworkReply best practices
}



BNBResponse * BNBClient::parse(QNetworkReply * rep)
{
    BNBResponse * resp = new BNBResponse(); // CALLER MUST DELETE THIS!

    QJsonParseError parseError; // error to pass by ref, just in case
    // read reply into QJsonDocument and try parse
    QJsonDocument doc = QJsonDocument::fromJson(rep->readAll(), &parseError);

    if (doc.isObject()) // should be BNBResponse serialized in JsonObject
    {
        resp->fromJson(doc.object()); // deserialize BNBResponse
    }
    else if (doc.isNull()) // parsing failed
    {
        resp->setError(parseError.errorString());
    }
    else
    {
        NetErr err = rep->error();
        if (err == NetErr::NoError) // good request, bad JSON type
        {
            resp->setError("Bad JSON response format");
        }
        else // unaccounted network error of some kind
        {
            resp->setError(rep->errorString());
        }
    }

    return resp; // don't forget to delete this response when you're done
}
