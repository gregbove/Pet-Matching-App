#ifndef PETATTRIBUTE_H
#define PETATTRIBUTE_H

#include <QString>
#include "bnbmodel.h"

class PetAttribute : public BNBModel
{
public:
    PetAttribute();
    ~PetAttribute();


    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    QString validation() const;



    QString getPetID() const;
    void setPetID(const QString &value);

    QString getAttributeID() const;
    void setAttributeID(const QString &value);

    QString getValue() const;
    void setValue(const QString &value);

private:
    static constexpr const char* PETID = "petID";
    static constexpr const char* ATTRIBUTEID = "attributeID";
    static constexpr const char* VALUE = "value";

    QString petID;
    QString attributeID;
    QString value;
};


#endif // PETATTRIBUTE_H
