#ifndef PETWATCH_H
#define PETWATCH_H


#include <memory>

#include <QString>
#include <QJsonObject>

#include "bnbmodel.h"
#include "parent.h"
#include "pet.h"

using namespace std;


class PetWatch : public BNBModel
{
public:
    PetWatch();
    ~PetWatch();

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

protected:
    static constexpr const char* PARENT_ID = "parentId";
    static constexpr const char* PARENT = "parent";
    static constexpr const char* PET_ID = "petId";
    static constexpr const char* PET = "pet";
    static constexpr const char* CREATED_AT = "createdAt";

    int parentId;
    shared_ptr<Parent> parent;
    int petId;
    shared_ptr<Pet>pet;
    QDateTime createdAt;
};

#endif // PETWATCH_H
