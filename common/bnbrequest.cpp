#include "bnbrequest.h"

BNBRequest::BNBRequest()
{
    payload = QJsonValue();
    type = QString();
}

void BNBRequest::fromJson(const QJsonObject &j)
{
    if (j.contains(PAYLOAD))
        payload = j[PAYLOAD];

    if (j.contains(TYPE) && j[TYPE].isString())
        type = j[TYPE].toString();
}

void BNBRequest::toJson(QJsonObject &j) const
{
    j[PAYLOAD] = payload;
    if (!type.isEmpty()) // type may be specified in URL
        j[TYPE] = type;
}

QJsonValue BNBRequest::getPayload() const
{
    return payload;
}

void BNBRequest::setPayload(const QJsonValue &value)
{
    payload = value;
}

QString BNBRequest::getType() const
{
    return type;
}

void BNBRequest::setType(const QString &value)
{
    type = value;
}
