#include "bnbmodel.h"

BNBModel::BNBModel()
{

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
