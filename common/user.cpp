#include "user.h"

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
    if (j.contains(USERNAME) && j[USERNAME].isString())
        username = j[USERNAME].toString();

    if (j.contains(PASSWORD) && j[PASSWORD].isString())
        password = j[PASSWORD].toString();

    if (j.contains(CREATED_AT) && j[CREATED_AT].isDouble())
        createdAt.setSecsSinceEpoch(j[CREATED_AT].toInt());
}

void User::toJson(QJsonObject &obj) const
{
    obj[USERNAME] = username;
    obj[PASSWORD] = password;
    obj[CREATED_AT] = createdAt.toSecsSinceEpoch();
}

bool User::isValid() const
{
    return false;
}

QString User::validation() const
{
    return QString();
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
