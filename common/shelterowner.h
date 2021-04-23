#ifndef SHELTEROWNER_H
#define SHELTEROWNER_H

#include <QString>

#include "shelter.h"
#include "user.h"

class ShelterOwner : public BNBModel
{
public:
    ShelterOwner();

    virtual void fromJson(const QJsonObject & obj);
    virtual void toJson(QJsonObject & obj) const;

    virtual QString validation() const;

    User & getUser();
    void setUser(const User &value);

    QString getName() const;
    void setName(const QString &value);



    int getShelterId() const;
    void setShelterId(int value);

    shared_ptr<Shelter> getShelter() const;
    void setShelter(const shared_ptr<Shelter> &value);

private:
    static constexpr const char* USER = "user";
    static constexpr const char* NAME = "name";
    static constexpr const char* SHELTER_ID = "shelterId";
    static constexpr const char* SHELTER = "shelter";


    User user;
    QString name;
    int shelterId;
    shared_ptr<Shelter> shelter;


};

#endif // SHELTEROWNER_Hxs

