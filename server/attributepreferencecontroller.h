#ifndef ATTRIBUTEPREFERENCECONTROLLER_H
#define ATTRIBUTEPREFERENCECONTROLLER_H


#include "../common/bnbresponse.h"
#include "../common/bnbrequest.h"
#include "../common/attributepreference.h"

#include "bnbcontroller.h"
#include "db.h"

#include <memory>
#include <restbed>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

using namespace std;
using namespace restbed;

/**
 * @brief Handles fetching and creating AttributePreference
 *
 * Endpoints:
 * /AttributePreference/{id: a postivive integer}
 *
 * > GET /AttributePreference
 * < a BNBResponse containing a list of AttributePreference
 *
 * > POST /AttributePreference
 * | a BNBRequest containing a AttributePreference to be created
 * < a BNBResponse containing the newly created AttributePreference or an error
 */
class AttributePreferenceController : public BNBController
{
public:
    AttributePreferenceController(QString baseUrl = "/attribute") : BNBController(baseUrl) {};

    void addToResource(const shared_ptr<Resource>);

protected:

    static constexpr const char* ID = "id";

    void getHandler(const shared_ptr<Session> session);
    void postHandler(const shared_ptr<Session> session);

};


#endif // ATTRIBUTEPREFERENCECONTROLLER_H
