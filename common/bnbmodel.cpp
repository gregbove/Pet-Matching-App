#include "bnbmodel.h"

BNBModel::BNBModel()
{
    id = 0;
}

void BNBModel::fromJson(const QJsonObject &j)
{
    if (j.contains(ID) && j[ID].isDouble())
            id = j[ID].toInt();
}

void BNBModel::toJson(QJsonObject &j) const
{
    j[ID] = id;
}

bool BNBModel::isValid() const
{
    return validation().isEmpty();
}

int BNBModel::getId() const
{
    return id;
}

void BNBModel::setId(int value)
{
    id = value;
}
