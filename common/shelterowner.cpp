#include "shelterowner.h"


ShelterOwner::ShelterOwner()
{
    user = User();
    name = QString();
    shelterID = QString();
    ownerID = QString();
}

void ShelterOwner::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(USER) && j[USER].isObject())
        user.fromJson(j[USER].toObject());

    if (j.contains(NAME) && j[NAME].isString())
        name = j[NAME].toString();

    if (j.contains(SHELTERID) && j[SHELTERID].isString())
        shelterID = j[SHELTERID].toString();

    if (j.contains(OWNERID) && j[OWNERID].isString())
        shelterID = j[OWNERID].toString();
}

void ShelterOwner::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    QJsonObject userObj;
    user.toJson(userObj);

    j[USER] = userObj;
    j[NAME] = name;
    j[SHELTERID] = shelterID;
    j[OWNERID] = ownerID;
}

QString ShelterOwner::validation() const
{
    QString v = user.validation();

    if (name.isEmpty())
        v += "name must not be empty\n";

    if (shelterID.isEmpty())
        v += "Shelter ID must not be empty\n";

    if (ownerID.isEmpty())
        v += "Owner ID must not be empty\n";

    return v;
}

User & ShelterOwner::getUser()
{
    return user;
}

void ShelterOwner::setUser(const User &value)
{
    user = value;
}

QString ShelterOwner::getName() const
{
    return name;
}

void ShelterOwner::setName(const QString &value)
{
    name = value;
}

QString ShelterOwner::getShelterID() const
{
    return shelterID;
}

void ShelterOwner::setShelterID(const QString &value)
{
    shelterID = value;
}

QString ShelterOwner::getOwnerID() const
{
    return ownerID;
}

void ShelterOwner::setOwnerID(const QString &value)
{
    ownerID = value;
}
