#ifndef PETMATCH_H
#define PETMATCH_H

#include <memory>

#include <QString>
#include <QJsonObject>

#include "bnbmodel.h"
#include "parent.h"
#include "pet.h"

using namespace std;


class PetMatch : public BNBModel
{
public:
    PetMatch();
    ~PetMatch();

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

    QDateTime getUpdatedAt() const;
    void setUpdatedAt(const QDateTime &value);

    double getScore() const;
    void setScore(double value);

protected:
    static constexpr const char* PARENT_ID = "parentId";
    static constexpr const char* PARENT = "parent";
    static constexpr const char* PET_ID = "petId";
    static constexpr const char* PET = "pet";
    static constexpr const char* UPDATED_AT = "updatedAt";
    static constexpr const char* SCORE = "score";

    int parentId;
    shared_ptr<Parent> parent;
    int petId;
    shared_ptr<Pet>pet;
    QDateTime updatedAt;
    double score;
};


#endif // PETMATCH_H
