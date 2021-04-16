#include "bnbresponse.h"

BNBResponse::BNBResponse()
{
    status = FAIL;
    error = QString();
}

void BNBResponse::fromJson(const QJsonObject &j)
{
    if (!j.contains(STATUS) || !j[STATUS].isString())
        return;

    QString statusStr = j[STATUS].toString();

    if (statusStr == STATUS_OK
            && j.contains(RESULT)
            && j[RESULT].isObject())
    {
        status = OK;
        result = j[RESULT].toObject();
    }
    else if (statusStr == STATUS_FAIL
             && j.contains(ERROR)
             && j[ERROR].isString())
    {
        status = FAIL;
        error = j[ERROR].toString();
    }
    else
    {
        status = FAIL;
        error = "Response deserialization failed";
    }
}

void BNBResponse::toJson(QJsonObject &j) const
{
    if (status == OK)
    {
        j[STATUS] = STATUS_OK;
        j[RESULT] = result;
    }
    else if (status == FAIL)
    {
        j[STATUS] = STATUS_FAIL;
        j[ERROR] = error;
    }
}

BNBResponseStatus BNBResponse::getStatus() const
{
    return status;
}

QJsonObject BNBResponse::getResult() const
{
    if (status != OK)
        throw "No result; status not OK";

    return result;
}

void BNBResponse::setResult(const QJsonObject &value)
{
    status = OK;
    result = value;
}

QString BNBResponse::getError() const
{
    return error;
}

void BNBResponse::setError(const QString &value)
{
    status = FAIL;
    error = value;
}
