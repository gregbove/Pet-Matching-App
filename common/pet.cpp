#include "pet.h"

Pet::Pet()
{
    petName = QString();
    shelterID = QString();
    description = QString();
}

Pet::~Pet()
{

}

void Pet::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(PETNAME) && j[petName].isString())
        petName = j[PETNAME].toString();

    if (j.contains(SHELTERID) && j[SHELTERID].isString())
        shelterID = j[SHELTERID].toString();

    if (j.contains(DESCRIPTION) && j[DESCRIPTION].isString())
        description = j[DESCRIPTION].toString();
}

void Pet::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    j[PETNAME] = petName;
    j[SHELTERID] = shelterID;
    j[DESCRIPTION] = description;
}

QString Pet::validation() const
{
    QString v;

    if (petName.isEmpty())
        v += "Pet name must not be empty\n";

    if (shelterID.isEmpty())
        v += "shelter ID must not be empty\n";

    if (description.isEmpty())
        v += "Description must not be empty\n";

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

QString Pet::getShelterID() const
{
    return shelterID;
}

void Pet::setShelterID(const QString &value)
{
    shelterID = value;
}

QString Pet::getDescription() const
{
    return description;
}

void Pet::setDescription(const QString &value)
{
    description = value;
}
