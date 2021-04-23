#include "petattribute.h"

PetAttribute::PetAttribute()
{
    petId = 0;
    attributeId = 0;
    value = 0;
}

PetAttribute::~PetAttribute()
{

}

void PetAttribute::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(PET_ID) && j[PET_ID].isString())
        petId = j[PET_ID].toInt();

    if (j.contains(ATTRIBUTE_ID) && j[ATTRIBUTE_ID].isString())
        attributeId = j[ATTRIBUTE_ID].toInt();

    if (j.contains(VALUE) && j[VALUE].isString())
        value = j[VALUE].toInt();

    if (j.contains(PET) && j[PET].isObject()){
        Pet petObj;
        petObj.fromJson(j[PET].toObject());
        pet = make_shared< Pet >( petObj );
    }

    if (j.contains(ATTRIBUTE) && j[ATTRIBUTE].isObject()){
        Attribute attributeObj;
        attributeObj.fromJson(j[ATTRIBUTE].toObject());
        attribute = make_shared< Attribute >( attributeObj );
    }

}

void PetAttribute::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    QJsonObject petObj;
    pet->toJson(petObj);

    QJsonObject attributeObj;
    attribute->toJson(attributeObj);

    j[PET_ID] = petId;
    j[ATTRIBUTE_ID] = attributeId;
    j[VALUE] = value;
    j[PET] = petObj;
    j[ATTRIBUTE] = attributeObj;
}

QString PetAttribute::validation() const
{
    QString v;

    if (pet == nullptr)
        v += "Pet must not be empty\n";

    if (attribute == nullptr)
        v += "Attribute must not be empty\n";

    // assume id must be positive
    if (petId <= 0)
        v += "Pet ID must not be negative or zero\n";

    if (attributeId <= 0)
        v += "Attribute ID must not be negative or zero\n";

    if(value < 0)
        v += "Value must be positive\n";


    return v;
}

int PetAttribute::getPetId() const
{
    return petId;
}

void PetAttribute::setPetId(int value)
{
    petId = value;
}

shared_ptr<Pet> PetAttribute::getPet() const
{
    return pet;
}

void PetAttribute::setPet(const shared_ptr<Pet> &value)
{
    pet = value;
}

int PetAttribute::getAttributeId() const
{
    return attributeId;
}

void PetAttribute::setAttributeId(int value)
{
    attributeId = value;
}

shared_ptr<Attribute> PetAttribute::getAttribute() const
{
    return attribute;
}

void PetAttribute::setAttribute(const shared_ptr<Attribute> &value)
{
    attribute = value;
}

int PetAttribute::getValue() const
{
    return value;
}

void PetAttribute::setValue(int val)
{
    value = val;
}


