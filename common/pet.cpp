#include "pet.h"

Pet::Pet()
{
    petName = QString();
    description = QString();
}

Pet::~Pet()
{

}

void Pet::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(PETNAME) && j[PETNAME].isString())
        petName = j[PETNAME].toString();

    if (j.contains(SHELTERID) && j[SHELTERID].isString())
        shelterId = j[SHELTERID].toInt();

    if (j.contains(DESCRIPTION) && j[DESCRIPTION].isString())
        description = j[DESCRIPTION].toString();

    if (j.contains(SHELTER) && j[SHELTER].isObject()){
        Shelter shelterObj;
        shelterObj.fromJson(j[SHELTER].toObject());
        shelter = make_shared< Shelter >( shelterObj );
    }

}

void Pet::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    QJsonObject shelterObj;
    shelter->toJson(shelterObj);

    j[PETNAME] = petName;
    j[SHELTERID] = shelterId;
    j[DESCRIPTION] = description;
    j[SHELTER] = shelterObj;

}

QString Pet::validation() const
{
    QString v;

    if (petName.isEmpty())
        v += "Pet name must not be empty\n";


    if (description.isEmpty())
        v += "Description must not be empty\n";

    if(shelter == nullptr)
        v += "shelter should not be null\n";

    if(shelterId <= 0)
        v += "shelter id should not be negative or zero\n";

    return v;
}

QString Pet::getPetName() const
{
    return petName;
}

void Pet::setPetName(const QString &value)
{
    petName = value;
}


QString Pet::getDescription() const
{
    return description;
}

void Pet::setDescription(const QString &value)
{
    description = value;
}

int Pet::getShelterId() const
{
    return shelterId;
}

void Pet::setShelterId(int value)
{
    shelterId = value;
}


shared_ptr<Shelter> Pet::getShelter() const
{
    return shelter;
}

void Pet::setShelter(const shared_ptr<Shelter> &value)
{
    shelter = value;
}
