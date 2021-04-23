#include "shelterownership.h"


ShelterOwnership::ShelterOwnership()
{

}

ShelterOwnership::~ShelterOwnership()
{

}

void ShelterOwnership::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(SHELTERID) && j[SHELTERID].isString())
        shelterId = j[SHELTERID].toInt();

    if (j.contains(OWNERID) && j[OWNERID].isString())
        ownerId = j[OWNERID].toInt();

    if (j.contains(OWNER) && j[OWNER].isObject()){
        ShelterOwner shelterOwnerObj;
        shelterOwnerObj.fromJson(j[OWNER].toObject());
        owner = make_shared< ShelterOwner >( shelterOwnerObj );
    }

    if (j.contains(SHELTER) && j[SHELTER].isObject()){
        Shelter shelterObj;
        shelterObj.fromJson(j[SHELTER].toObject());
        shelter = make_shared< Shelter >( shelterObj );
    }
}

void ShelterOwnership::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    QJsonObject shelterObj;
    shelter->toJson(shelterObj);

    QJsonObject shelterOwnerObj;
    owner->toJson(shelterOwnerObj);

    j[SHELTERID] = shelterId;
    j[OWNERID] = ownerId;
    j[SHELTER] = shelterObj;
    j[OWNER] = shelterOwnerObj;
}

QString ShelterOwnership::validation() const
{
    QString v;

    if (shelterId <= 0)
        v += "Shelter ID must not be negative or zero\n";

    if (ownerId <= 0)
        v += "Owner ID must not be negative or zero\n";

    if (shelter == nullptr)
        v += "shelter must not be null\n";

    if (owner == nullptr)
        v += "owner must not be null\n";

    return v;
}

int ShelterOwnership::getOwnerId() const
{
    return ownerId;
}

void ShelterOwnership::setOwnerId(int value)
{
    ownerId = value;
}

shared_ptr<ShelterOwner> ShelterOwnership::getShelterOwner() const
{
    return owner;
}

void ShelterOwnership::setShelterOwner(const shared_ptr<ShelterOwner> &value)
{
    owner = value;
}

int ShelterOwnership::getShelterId() const
{
    return shelterId;
}

void ShelterOwnership::setShelterId(int value)
{
    shelterId = value;
}

shared_ptr<Shelter> ShelterOwnership::getShelter() const
{
    return shelter;
}

void ShelterOwnership::setShelter(const shared_ptr<Shelter> &value)
{
    shelter = value;
}

