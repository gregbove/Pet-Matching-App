#include "petmatch.h"

PetMatch::PetMatch()
{
    petId = 0;
    parentId = 0;
    updatedAt = QDateTime();
    score = 0;
}

PetMatch::~PetMatch()
{

}

void PetMatch::fromJson(const QJsonObject &j)
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

    if (j.contains(UPDATED_AT) && j[UPDATED_AT].isDouble())
        updatedAt.setSecsSinceEpoch(j[UPDATED_AT].toInt());

    if (j.contains(SCORE) && j[SCORE].isDouble())
        score = j[SCORE].toDouble();

}

void PetMatch::toJson(QJsonObject &j) const
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
    j[UPDATED_AT] = updatedAt.toSecsSinceEpoch();
    j[SCORE] = score;

}

QString PetMatch::validation() const
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

    if (!updatedAt.isValid())
        v += "updatedAt must be a valid date-time\n";



    return v;
}

int PetMatch::getParentId() const
{
    return parentId;
}

void PetMatch::setParentId(int value)
{
    parentId = value;
}

shared_ptr<Parent> PetMatch::getParent() const
{
    return parent;
}

void PetMatch::setParent(const shared_ptr<Parent> &value)
{
    parent = value;
}

int PetMatch::getPetId() const
{
    return petId;
}

void PetMatch::setPetId(int value)
{
    petId = value;
}

shared_ptr<Pet> PetMatch::getPet() const
{
    return pet;
}

void PetMatch::setPet(const shared_ptr<Pet> &value)
{
    pet = value;
}

QDateTime PetMatch::getUpdatedAt() const
{
    return updatedAt;
}

void PetMatch::setUpdatedAt(const QDateTime &value)
{
    updatedAt = value;
}

double PetMatch::getScore() const
{
    return score;
}

void PetMatch::setScore(double value)
{
    score = value;
}
