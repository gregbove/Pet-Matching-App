#ifndef PET_H
#define PET_H

#include <memory>

#include <QString>
#include <QJsonObject>

#include "bnbmodel.h"
#include "shelter.h"

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


    QString getDescription() const;
    void setDescription(const QString &value);

    int getShelterId() const;
    void setShelterId(int value);

    shared_ptr<Shelter> getShelter() const;
    void setShelter(const shared_ptr<Shelter> &value);

protected:
    static constexpr const char* PETNAME = "petName";
    static constexpr const char* SHELTER_ID = "shelterId";
    static constexpr const char* SHELTER = "shelter";
    static constexpr const char* DESCRIPTION = "description";

    QString petName;
    int shelterId;
    shared_ptr<Shelter> shelter;
    QString description;
};

#endif // PET_H
