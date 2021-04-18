#ifndef BNBRESPONSE_H
#define BNBRESPONSE_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>

#include "jsonserializable.h"

/**
 * @brief The success-status of a BNBResponse
 *
 * BNBResponses handle serializing this as a string,
 * so you can just use it natively to check/set statuses.
 */
enum BNBResponseStatus
{
    OK,  /// "The request produced the expected result"
    FAIL /// "The something happened either with the server or with the request
         /// that prevented the server from returning the expected result."
};

/**
 * @brief A response recieved from the BNB server as a JSON message body
 *
 * A response always contains a status indicating whether it succeeded
 * or failed. If the response succeeded, it will have a result, and if it
 * failed, it will have an error. Always check a response's status before
 * trying to get it's result/error.
 *
 * A sample response might look like this:
 * {
 *   "error": "something bad happened",
 *   "status": "fail"
 * }
 *
 * or like this:
 * {
 *   "result": [
 *     {
 *       "name": "Sandy Elmwood",
 *       "user": {
 *         "id": 1,
 *       }
 *     }
 *   ],
 *   "status": "ok"
 * }
 */
class BNBResponse : public JSONSerializable
{
public:
    BNBResponse();

    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    BNBResponseStatus getStatus() const;
    void setStatus(const BNBResponseStatus &value);

    /**
     * @brief Gets the result, assuming the response was OK
     * @return a JSON value of the result
     *
     * If the response was not OK, this method will
     * throw an exception! Make sure to check the status first.
     */
    QJsonValue getResult() const;
    void setResult(const QJsonValue &value);

    /**
     * @brief Gets the error, assuming the response failed
     * @return a QString containing the error
     *
     * This method will return a null-valued QString if
     * no error was present (ie if the response was OK).
     */
    QString getError() const;
    void setError(const QString &value);

protected:
    static constexpr const char* RESULT = "result";
    static constexpr const char* ERROR = "error";
    static constexpr const char* STATUS = "status";
    static constexpr const char* STATUS_OK = "ok";
    static constexpr const char* STATUS_FAIL = "fail";

    BNBResponseStatus status;
    QJsonValue result;
    QString error;
};

#endif // BNBRESPONSE_H
