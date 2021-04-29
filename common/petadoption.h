#ifndef PETADOPTION_H
#define PETADOPTION_H

#include <memory>

#include <QString>
#include <QJsonObject>

#include "bnbmodel.h"
#include "parent.h"
#include "pet.h"

using namespace std;


class PetAdoption : public BNBModel
{
public:
    PetAdoption();
    ~PetAdoption();

    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    QString validation() const;


    int getParentId() const;
    void setParentId(int value);

    shared_ptr<Parent> getParent() const;
    void setParent(const shared_ptr<Parent> &value);

    int getPetId() const;
    void setPetId(int value);

    shared_ptr<Pet> getPet() const;
    void setPet(const shared_ptr<Pet> &value);

    QDateTime getCreatedAt() const;
    void setCreatedAt(const QDateTime &value);

    bool getActive() const;
    void setActive(bool value);

    bool getApproved() const;
    void setApproved(bool value);

protected:
    static constexpr const char* PARENT_ID = "parentId";
    static constexpr const char* PARENT = "parent";
    static constexpr const char* PET_ID = "petId";
    static constexpr const char* PET = "pet";
    static constexpr const char* CREATED_AT = "createdAt";
    static constexpr const char* ACTIVE = "active";
    static constexpr const char* APPROVED = "approved";

    int parentId;
    shared_ptr<Parent> parent;
    int petId;
    shared_ptr<Pet>pet;
    QDateTime createdAt;
    bool active;
    bool approved;
};

#endif // PETADOPTION_H
