#ifndef BNBMODEL_H
#define BNBMODEL_H

#include <QString>
#include <QJsonObject>

/**
 * @brief Abstract parent for all data-model classes in Bread-N-Butter
 *
 * This class includes methods (and necessary default implementations)
 * that must be implemented for all models.
 */
class BNBModel
{
public:
    BNBModel();

    /**
     * @brief Set this model's instance variables from a JSON object.
     * @param obj a QJsonObject containing any appropriate fields
     *
     * Implementations of this method should only update instance variables
     * when for coorisponding fields when they are present in the QJsonObject
     * and of the correct type. Missing or irrelevent fields should be ignored.
     */
    virtual void fromJson(const QJsonObject & obj) = 0;

    /**
     * @brief Add fields to a QJsonObject for each
     *          of this model's instance variables.
     * @param obj a QJsonObject to recieve the new fields.
     *
     * Implementations of this method should accept any QJsonObject
     * regardless of existing fields it may contain. Appropriate fields in the
     * object will be set/overridden with the model's instance variables.
     */
    virtual void toJson(QJsonObject & obj) const = 0;

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
