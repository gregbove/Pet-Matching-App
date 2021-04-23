#ifndef PETATTRIBUTE_H
#define PETATTRIBUTE_H

#include <QString>
#include "attribute.h"
#include "bnbmodel.h"
#include "pet.h"

class PetAttribute : public BNBModel
{
public:
    PetAttribute();
    ~PetAttribute();


    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    QString validation() const;

    int getPetId() const;
    void setPetId(int value);

    shared_ptr<Pet> getPet() const;
    void setPet(const shared_ptr<Pet> &value);

    int getAttributeId() const;
    void setAttributeId(int value);

    shared_ptr<Attribute> getAttribute() const;
    void setAttribute(const shared_ptr<Attribute> &value);

    int getValue() const;
    void setValue(int val);

private:
    static constexpr const char* PETID = "petId";
    static constexpr const char* ATTRIBUTEID = "attributeId";
    static constexpr const char* VALUE = "value";
    static constexpr const char* PET = "pet";
    static constexpr const char* ATTRIBUTE = "attribute";

    int petId;
    shared_ptr<Pet> pet;
    int attributeId;
    shared_ptr<Attribute> attribute;
    int value;
};


#endif // PETATTRIBUTE_H
