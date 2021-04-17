#include "parent.h"

Parent::Parent()
{
    user = User();
    name = QString();
}

void Parent::fromJson(const QJsonObject &j)
{
    if (j.contains(USER) && j[USER].isObject())
        user.fromJson(j[USER].toObject());

    if (j.contains(NAME) && j[NAME].isString())
        name = j[NAME].toString();
}

void Parent::toJson(QJsonObject &j) const
{
    QJsonObject userObj;
    user.toJson(userObj);

    j[USER] = userObj;
    j[NAME] = name;
}

QString Parent::validation() const
{
    QString v = user.validation();

    if (name.isEmpty())
        v += "name must not be empty\n";

    return v;
}

User & Parent::getUser()
{
    return user;
}

void Parent::setUser(const User &value)
{
    user = value;
}

QString Parent::getName() const
{
    return name;
}

void Parent::setName(const QString &value)
{
    name = value;
}
