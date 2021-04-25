#include "bnbclient.h"

typedef QNetworkReply::NetworkError NetErr;

BNBClient::BNBClient(QUrl baseUrl, QObject *parent) : QObject(parent)
{
    baseUrl.setPath("");
    base = baseUrl;
}

void BNBClient::getParents()
{
    QUrl pUrl(base);
    pUrl.setPath("/users/parents");

    QNetworkRequest req(pUrl);

    QNetworkReply * rep = man.get(req);

    connect(rep, &QNetworkReply::finished, this, &BNBClient::getParentsFinish);
}

void BNBClient::postParent(Parent &p)
{
    QUrl pUrl(base);
    pUrl.setPath("/users/parents");

    QJsonObject po;
    p.toJson(po);

    BNBRequest br;
    br.setPayload(po);

    QJsonObject ro;
    br.toJson(ro);

    QJsonDocument doc;
    doc.setObject(ro);

    QByteArray body = doc.toJson();

    QNetworkRequest req(pUrl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(body.length()));

    QNetworkReply * rep = man.post(req, body);

    connect(rep, &QNetworkReply::finished, this, &BNBClient::postParentFinish);
}

void BNBClient::getParentsFinish()
{
    QNetworkReply * reply =  (QNetworkReply *) sender();
    BNBResponse * res = parse(reply);

    if (res->getStatus() == OK)
    {
        QJsonArray arr = res->getResult().toArray();
        QVector<shared_ptr<Parent>> ps;

        for (QJsonValue v : arr)
        {
            shared_ptr<Parent> p = make_shared<Parent>();
            QJsonObject o = v.toObject();
            p->fromJson(o);
            ps.append(p);
        }

        getParentsSucceeded(ps);
    }
    else
    {
        getParentsFailed(res->getError());
    }

    delete res;
    reply->deleteLater();
}

void BNBClient::postParentFinish()
{
    QNetworkReply * reply =  (QNetworkReply *) sender();
    BNBResponse * res = parse(reply);

    if (res->getStatus() == OK)
    {
        const shared_ptr<Parent> p = make_shared<Parent>();
        QJsonObject o = res->getResult().toObject();
        p->fromJson(o);

        postParentSucceeded(p);
    }
    else
    {
        postParentFailed(res->getError());
    }

    delete res;
    reply->deleteLater();
}

BNBResponse * BNBClient::parse(QNetworkReply * rep)
{
    BNBResponse * resp = new BNBResponse();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(rep->readAll(), &parseError);

    if (doc.isObject())
    {
        resp->fromJson(doc.object());
    }
    else if (doc.isNull())
    {
        resp->setError(parseError.errorString());
    }
    else
    {
        NetErr err = rep->error();
        if (err == NetErr::NoError)
        {
            resp->setError("Bad JSON response format");
        }
        else
        {
            resp->setError(rep->errorString());
        }
    }

    return resp;
}
