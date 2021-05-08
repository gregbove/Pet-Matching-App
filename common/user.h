#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

#include "bnbmodel.h"

using namespace std;

enum UserType {
    PARENT, SHELTER_OWNER, ADMINISTRATOR
};

/**
 * @brief A user of the Bread-N-Butter application
 *
 * User objects should be stored in JSON in the folowing form:
 * {
 *      "username": "SomeUser", (should be unique)
 *      "password": "$omePassw0rd", (should be non-empty)
 *      "createdAt": 1618089764 (number of seconds since Unix Epoch)
 * }
 */
class User : public BNBModel
{
public:
    static QString getTypeStr(UserType t);

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
