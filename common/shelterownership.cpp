#include "shelterownership.h"


ShelterOwnership::ShelterOwnership()
{
    shelterID = QString();
    ownerID = QString();
}

ShelterOwnership::~ShelterOwnership()
{

}

void ShelterOwnership::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(SHELTERID) && j[SHELTERID].isString())
        shelterID = j[SHELTERID].toString();
    if (j.contains(OWNERID) && j[OWNERID].isString())
        ownerID = j[OWNERID].toString();
}

void ShelterOwnership::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    j[SHELTERID] = shelterID;
    j[OWNERID] = ownerID;
}

QString ShelterOwnership::validation() const
{
    QString v;

    if (shelterID.isEmpty())
        v += "Shelter ID must not be empty\n";

    if (ownerID.isEmpty())
            v += "Owner ID must not be empty\n";

    return v;
}

QString ShelterOwnership::getShelterID() const
{
    return shelterID;
}

void ShelterOwnership::setShelterID(const QString &value)
{
    shelterID = value;
}


QString ShelterOwnership::getOwnerID() const
{
    return ownerID;
}

void ShelterOwnership::setOwnerID(const QString &value)
{
    ownerID = value;
}
