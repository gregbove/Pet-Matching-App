#ifndef SHELTEROWNERSHIP_H
#define SHELTEROWNERSHIP_H

#include <QString>
#include "bnbmodel.h"
#include "shelterowner.h"

class ShelterOwnership : public BNBModel
{
public:
    ShelterOwnership();
    ~ShelterOwnership();

    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    QString validation() const;


    int getOwnerId() const;
    void setOwnerId(int value);

    shared_ptr<ShelterOwner> getShelterOwner() const;
    void setShelterOwner(const shared_ptr<ShelterOwner> &value);

    int getShelterId() const;
    void setShelterId(int value);

    shared_ptr<Shelter> getShelter() const;
    void setShelter(const shared_ptr<Shelter> &value);

private:
    static constexpr const char* OWNER_ID = "ownerId";
    static constexpr const char* SHELTER_ID = "shelterId";
    static constexpr const char* OWNER = "owner";
    static constexpr const char* SHELTER = "shelter";

    int ownerId;
    shared_ptr<ShelterOwner> owner;
    int shelterId;
    shared_ptr<Shelter> shelter;
};

#endif // SHELTEROWNERSHIP_H
