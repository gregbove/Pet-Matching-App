#include "bnbmodel.h"

BNBModel::BNBModel()
{

}

bool BNBModel::isValid() const
{
    return validation().isEmpty();
}
