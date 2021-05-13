#ifndef ATTRIBUTECONTROLLER_H
#define ATTRIBUTECONTROLLER_H

#include "../common/bnbresponse.h"
#include "../common/bnbrequest.h"
#include "../common/attribute.h"

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
 * @brief Handles fetching and creating Attributes
 *
 * Endpoints:
 * /attribute/{id: a postivive integer}
 *
 * > GET /attribute
 * < a BNBResponse containing a list of Attributes
 *
 * > POST /attribute
 * | a BNBRequest containing a attribute to be created
 * < a BNBResponse containing the newly created attribute or an error
 */
class AttributeController : public BNBController
{
public:
    AttributeController(QString baseUrl = "/attributes") : BNBController(baseUrl) {};

    void addToResource(const shared_ptr<Resource>);

protected:

    static constexpr const char* ID = "id";

    void getHandler(const shared_ptr<Session> session);
    void postHandler(const shared_ptr<Session> session);

};


#endif // ATTRIBUTECONTROLLER_H
