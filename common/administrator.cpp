#include "administrator.h"


Administrator::Administrator()
{
    user = User();
    isSuperAdmin = false;
}

void Administrator::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(USER) && j[USER].isObject())
        user.fromJson(j[USER].toObject());

    if (j.contains(ISSUPERADMIN))
        isSuperAdmin = j[ISSUPERADMIN].toString()=="true";
}

void Administrator::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    QJsonObject userObj;
    user.toJson(userObj);

    j[USER] = userObj;
    j[ISSUPERADMIN] = isSuperAdmin;
}

QString Administrator::validation() const
{
    QString v = user.validation();

    return v;
}

User & Administrator::getUser()
{
    return user;
}

void Administrator::setUser(const User &value)
{
    user = value;
}


bool Administrator::getIsSuperAdmin() const
{
    return isSuperAdmin;
}

void Administrator::setIsSuperAdmin(bool value)
{
    isSuperAdmin = value;
}
