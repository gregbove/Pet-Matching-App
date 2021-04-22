#ifndef PET_H
#define PET_H

#include <QString>
#include <QJsonObject>

#include "bnbmodel.h"

using namespace std;


class Pet : public BNBModel
{
public:
    Pet();
     ~Pet();

    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    QString validation() const;

    QString getPetName() const;
    void setPetName(const QString &value);

    QString getShelterID() const;
    void setShelterID(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

protected:
    static constexpr const char* PETNAME = "petName";
    static constexpr const char* SHELTERID = "shelterID";
    static constexpr const char* DESCRIPTION = "description";

    QString petName;
    QString shelterID;
    QString description;
};

#endif // PET_H
