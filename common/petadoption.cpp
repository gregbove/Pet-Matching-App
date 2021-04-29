#include "petadoption.h"


PetAdoption::PetAdoption()
{
    petId = 0;
    parentId = 0;
    createdAt = QDateTime();
    active = false;
    approved = false;
    ;
}

PetAdoption::~PetAdoption()
{

}

void PetAdoption::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id


    if (j.contains(PARENT_ID) && j[PARENT_ID].isString())
        parentId = j[PARENT_ID].toInt();

    if (j.contains(PET_ID) && j[PET_ID].isString())
        petId = j[PET_ID].toInt();

    if (j.contains(PARENT) && j[PARENT].isObject()){
        Parent parentObj;
        parentObj.fromJson(j[PARENT].toObject());
        parent = make_shared< Parent >( parentObj );
    }

    if (j.contains(PET) && j[PET].isObject()){
        Pet petObj;
        petObj.fromJson(j[PET].toObject());
        pet = make_shared< Pet >( petObj );
    }

    if (j.contains(CREATED_AT) && j[CREATED_AT].isDouble())
        createdAt.setSecsSinceEpoch(j[CREATED_AT].toInt());

    if (j.contains(ACTIVE))
        active = j[ACTIVE].toString()=="true";

    if (j.contains(APPROVED))
        approved = j[ACTIVE].toString()=="true";

}

void PetAdoption::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    QJsonObject petObj;
    pet->toJson(petObj);

    QJsonObject parentObj;
    parent->toJson(parentObj);

    j[PET] = petObj;
    j[PARENT] = parentObj;
    j[PET_ID] = petId;
    j[PARENT_ID] = parentId;
    j[CREATED_AT] = createdAt.toSecsSinceEpoch();
    j[ACTIVE] = active;
    j[APPROVED] = approved;


}

QString PetAdoption::validation() const
{
    QString v;

    if(parent == nullptr)
        v += "parent should not be null\n";

    if(parentId <= 0)
        v += "parent id should not be negative or zero\n";


    if(pet == nullptr)
        v += "pet should not be null\n";

    if(petId <= 0)
        v += "pet id should not be negative or zero\n";

    if (!createdAt.isValid())
        v += "updatedAt must be a valid date-time\n";



    return v;
}

int PetAdoption::getParentId() const
{
    return parentId;
}

void PetAdoption::setParentId(int value)
{
    parentId = value;
}

shared_ptr<Parent> PetAdoption::getParent() const
{
    return parent;
}

void PetAdoption::setParent(const shared_ptr<Parent> &value)
{
    parent = value;
}

int PetAdoption::getPetId() const
{
    return petId;
}

void PetAdoption::setPetId(int value)
{
    petId = value;
}

shared_ptr<Pet> PetAdoption::getPet() const
{
    return pet;
}

void PetAdoption::setPet(const shared_ptr<Pet> &value)
{
    pet = value;
}

QDateTime PetAdoption::getCreatedAt() const
{
    return createdAt;
}

void PetAdoption::setCreatedAt(const QDateTime &value)
{
    createdAt = value;
}

bool PetAdoption::getActive() const
{
    return active;
}

void PetAdoption::setActive(bool value)
{
    active = value;
}

bool PetAdoption::getApproved() const
{
    return approved;
}

void PetAdoption::setApproved(bool value)
{
    approved = value;
}
