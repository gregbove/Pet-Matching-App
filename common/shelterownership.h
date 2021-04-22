#ifndef SHELTEROWNERSHIP_H
#define SHELTEROWNERSHIP_H

#include <QString>
#include "bnbmodel.h"

class ShelterOwnership : public BNBModel
{
public:
    ShelterOwnership();
    ~ShelterOwnership();

    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    QString validation() const;

    QString getShelterID() const;
    void setShelterID(const QString &value);

    QString getOwnerID() const;
    void setOwnerID(const QString &value);

private:
    static constexpr const char* OWNERID = "ownerID";
    static constexpr const char* SHELTERID = "shelterID";

    QString ownerID;
    QString shelterID;
};

#endif // SHELTEROWNERSHIP_H
