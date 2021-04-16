#ifndef BNBMODEL_H
#define BNBMODEL_H

#include <QString>

#include "jsonserializable.h"

/**
 * @brief Abstract parent for all data-model classes in Bread-N-Butter
 *
 * This class includes methods (and necessary default implementations)
 * that must be implemented for all models.
 */
class BNBModel : public JSONSerializable
{
public:
    BNBModel();

    /**
     * @brief Checks if the model meets all of its validation
     *          criteria in its current state.
     * @return false if there is at least one validation error, true otherwise
     */
    virtual bool isValid() const;

    /**
     * @brief Get a string containing all validation error messages.
     * @return A QString containing all validation error messages.
     *
     * Validation error messages shall be separated by a newline
     * character and may contain a trailing newline. If no validation
     * errors are found, this method shallll return an empty QString.
     */
    virtual QString validation() const = 0;
};

#endif // BNBMODEL_H
