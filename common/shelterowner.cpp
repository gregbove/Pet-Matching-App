#include "shelterowner.h"


ShelterOwner::ShelterOwner()
{
    user = User();
    name = QString();
    shelterId = 0;
}

void ShelterOwner::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(USER) && j[USER].isObject())
        user.fromJson(j[USER].toObject());

    if (j.contains(NAME) && j[NAME].isString())
        name = j[NAME].toString();

    if (j.contains(SHELTER_ID) && j[SHELTER_ID].isDouble())
        shelterId = j[SHELTER_ID].toInt();

    if (j.contains(SHELTER) && j[SHELTER].isObject()){
        Shelter shelterObj;
        shelterObj.fromJson(j[SHELTER].toObject());
        shelter = make_shared< Shelter >( shelterObj );
    }

}

void ShelterOwner::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    QJsonObject userObj;
    user.toJson(userObj);

    if (shelter != nullptr)
    {
        QJsonObject shelterObj;
        shelter->toJson(shelterObj);
        j[SHELTER] = shelterObj;
    }

    j[USER] = userObj;
    j[NAME] = name;
    j[SHELTER_ID] = shelterId;
}

QString ShelterOwner::validation() const
{
    QString v = user.validation();

    if (name.isEmpty())
        v += "name must not be empty\n";

    if (shelterId <= 0)
        v += "Shelter ID must not be negative or zero\n";

    return v;
}


//
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

int ShelterOwner::getShelterId() const
{
    return shelterId;
}

void ShelterOwner::setShelterId(int value)
{
    shelterId = value;
}

shared_ptr<Shelter> ShelterOwner::getShelter() const
{
    return shelter;
}

void ShelterOwner::setShelter(const shared_ptr<Shelter> &value)
{
    shelter = value;
}


