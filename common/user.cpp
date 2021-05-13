#include "user.h"

QString User::getTypeStr(UserType t)
{
    switch (t) {
    case PARENT:
        return "parent";
    case SHELTER_OWNER:
        return "shelterOwner";
    case ADMINISTRATOR:
        return "administrator";
    default:
        return QString();
    }
}

UserType User::getType(QString t)
{
    t = t.toLower();

    if (t.startsWith("parent"))
    {
        return PARENT;
    }
    else if (t.startsWith("shelterowner"))
    {
        return SHELTER_OWNER;
    }
    else if (t.startsWith("admin"))
    {
        return ADMINISTRATOR;
    }

    return INVALID_USER_TYPE;
}

User::User()
{
    username = QString();
    password = QString();
    createdAt = QDateTime();
}

User::~User()
{

}

void User::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(USERNAME) && j[USERNAME].isString())
        username = j[USERNAME].toString();

    if (j.contains(PASSWORD) && j[PASSWORD].isString())
        password = j[PASSWORD].toString();

    if (j.contains(CREATED_AT) && j[CREATED_AT].isDouble())
        createdAt.setSecsSinceEpoch(j[CREATED_AT].toInt());
}

void User::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    j[USERNAME] = username;
    j[PASSWORD] = password;
    j[CREATED_AT] = createdAt.toSecsSinceEpoch();
}

QString User::validation() const
{
    QString v;

    if (username.isEmpty())
        v += "username must not be empty\n";

    if (password.isEmpty())
        v += "password must not be empty\n";

    if (!createdAt.isValid())
        v += "createdAt must be a valid date-time\n";

    return v;
}

// === Getters and Setters ===

QString User::getUsername() const
{
    return username;
}

void User::setUsername(const QString &value)
{
    username = value;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &value)
{
    password = value;
}

QDateTime User::getCreatedAt() const
{
    return createdAt;
}

void User::setCreatedAt(const QDateTime &value)
{
    createdAt = value;
}
