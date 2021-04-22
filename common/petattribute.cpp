#include "petattribute.h"

PetAttribute::PetAttribute()
{
    petID = QString();
    attributeID = QString();
    value = QString();
}

PetAttribute::~PetAttribute()
{

}

void PetAttribute::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(PETID) && j[PETID].isString())
        petID = j[PETID].toString();
    if (j.contains(ATTRIBUTEID) && j[ATTRIBUTEID].isString())
        attributeID = j[ATTRIBUTEID].toString();
    if (j.contains(VALUE) && j[VALUE].isString())
        value = j[VALUE].toString();
}

void PetAttribute::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    j[PETID] = petID;
    j[ATTRIBUTEID] = attributeID;
    j[VALUE] = value;
}

QString PetAttribute::validation() const
{
    QString v;

    if (petID.isEmpty())
        v += "Pet ID must not be empty\n";

    if (attributeID.isEmpty())
            v += "Attribute ID must not be empty\n";

    if (value.isEmpty())
            v += "Value must not be empty\n";

    return v;
}

QString PetAttribute::getPetID() const
{
    return petID;
}

void PetAttribute::setPetID(const QString &value)
{
    petID = value;
}

QString PetAttribute::getAttributeID() const
{
    return attributeID;
}

void PetAttribute::setAttributeID(const QString &value)
{
    attributeID = value;
}

QString PetAttribute::getValue() const
{
    return value;
}

void PetAttribute::setValue(const QString &val)
{
    value = val;
}
