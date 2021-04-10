#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

#include "bnbmodel.h"

using namespace std;

class User : public BNBModel
{
public:
    User();
    virtual ~User();

    virtual void fromJson(const QJsonObject & obj);
    virtual void toJson(QJsonObject & obj) const;

    virtual QString validation() const;

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QDateTime getCreatedAt() const;
    void setCreatedAt(const QDateTime &value);

protected:
    static constexpr const char* USERNAME = "username";
    static constexpr const char* PASSWORD = "password";
    static constexpr const char* CREATED_AT = "createdAt";

    QString username;
    QString password;
    QDateTime createdAt;
};

#endif // USER_H
