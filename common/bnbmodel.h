#ifndef BNBMODEL_H
#define BNBMODEL_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>

#include "jsonserializable.h"

/**
 * @brief Abstract parent for all data-model classes in Bread-N-Butter
 *
 * This class includes methods (and necessary default implementations)
 * that must be implemented for all models. This should also be referenced
 * for any general documentation pertaining to models.
 */
class BNBModel : public JSONSerializable
{
public:
    BNBModel();

    /**
     * @brief Load a BNBModel from a JSON Object
     * @param obj the Object to load from
     *
     * This method should be overridden but the overriding method
     * must call this method in order to deserialize the Model id
     */
    virtual void fromJson(const QJsonObject & obj);

    /**
     * @brief Store a BNBModel to a JSON Object
     * @param obj the Object to save to
     *
     * This method should be overridden but the overriding method
     * must call this method in order to serialize the Model id
     */
    virtual void toJson(QJsonObject & obj) const;

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

    /// Every model has an id. Models should extend BNBModel and therefore
    /// should not implement their own id (but must serialize it).
    int getId() const;
    void setId(int value);

protected:
    static constexpr const char* ID = "id";

    int id;
};

#endif // BNBMODEL_H
