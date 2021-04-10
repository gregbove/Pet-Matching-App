#ifndef BNBMODEL_H
#define BNBMODEL_H

#include <QString>
#include <QJsonObject>

class BNBModel
{
public:
    BNBModel();

    virtual void fromJson(const QJsonObject & obj) = 0;
    virtual void toJson(QJsonObject & obj) const = 0;

    virtual bool isValid() const = 0;
    virtual QString validation() const = 0;
};

#endif // BNBMODEL_H
