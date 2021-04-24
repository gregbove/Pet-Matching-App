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
    req.setRawHeader("Content-Type", "application/json");

    QNetworkReply * rep = man.get(req);

    connect(rep, &QNetworkReply::finished, this, &BNBClient::getParentsFinish);
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
}

BNBResponse * BNBClient::parse(QNetworkReply * rep)
{
    BNBResponse * resp = new BNBResponse();

    NetErr err = rep->error();
    if (err == NetErr::NoError)
    {
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
            resp->setError("Bad JSON response type");
        }
    }
    else
    {
        resp->setError("Network error");
    }

    return resp;
}
