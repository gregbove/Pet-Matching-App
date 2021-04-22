#ifndef SHELTEROWNER_H
#define SHELTEROWNER_H

#include <QString>

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

    QString getShelterID() const;
    void setShelterID(const QString &value);

    QString getOwnerID() const;
    void setOwnerID(const QString &value);

private:
    static constexpr const char* USER = "user";
    static constexpr const char* NAME = "name";
    static constexpr const char* SHELTERID = "shelterID";
    static constexpr const char* OWNERID = "ownerID";

    User user;
    QString name;
    QString shelterID;
    QString ownerID;
};

#endif // SHELTEROWNER_Hxs

