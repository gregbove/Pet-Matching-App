#ifndef BNBREQUEST_H
#define BNBREQUEST_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>

#include "jsonserializable.h"

class BNBRequest : public JSONSerializable
{
public:
    BNBRequest();

    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    QJsonValue getPayload() const;
    void setPayload(const QJsonValue &value);

    QString getType() const;
    void setType(const QString &value);

protected:
    static constexpr const char* PAYLOAD = "payload";
    static constexpr const char* TYPE = "type";

    QJsonValue payload;
    QString type;
};

#endif // BNBREQUEST_H
