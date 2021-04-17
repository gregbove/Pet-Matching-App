#ifndef BNBRESPONSE_H
#define BNBRESPONSE_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>

#include "jsonserializable.h"

enum BNBResponseStatus
{
    OK,
    FAIL
};

class BNBResponse : public JSONSerializable
{
public:
    BNBResponse();

    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    BNBResponseStatus getStatus() const;
    void setStatus(const BNBResponseStatus &value);

    QJsonValue getResult() const;
    void setResult(const QJsonValue &value);

    QString getError() const;
    void setError(const QString &value);

protected:
    static constexpr const char* RESULT = "result";
    static constexpr const char* ERROR = "error";
    static constexpr const char* STATUS = "status";
    static constexpr const char* STATUS_OK = "ok";
    static constexpr const char* STATUS_FAIL = "fail";

    BNBResponseStatus status;
    QJsonValue result;
    QString error;
};

#endif // BNBRESPONSE_H
