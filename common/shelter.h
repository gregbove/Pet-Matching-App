#ifndef SHELTER_H
#define SHELTER_H

#include <QString>
#include <QJsonObject>

#include "bnbmodel.h"

using namespace std;


class Shelter : public BNBModel
{
public:
    Shelter();
    ~Shelter();

    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    QString validation() const;

    QString getName() const;
    void setName(const QString &value);

protected:
    static constexpr const char* NAME = "name";


    QString name;

};

#endif // SHELTER_H
