#ifndef JSONSERIALIZABLE_H
#define JSONSERIALIZABLE_H

#include <QJsonObject>

/**
 * @brief An abstract parent class representing objects
 * that can be serialized and deserialized from JSON.
 */
class JSONSerializable
{
public:
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
};

#endif // JSONSERIALIZABLE_H
