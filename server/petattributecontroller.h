#ifndef PETATTRIBUTECONTROLLER_H
#define PETATTRIBUTECONTROLLER_H


#include "../common/bnbresponse.h"
#include "../common/bnbrequest.h"
#include "../common/petattribute.h"

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
 * > GET /petAttribute
 * < a BNBResponse containing a list of PetAttributes
 *
 * > POST /petAttribute
 * | a BNBRequest containing a pet attribute to be created
 * < a BNBResponse containing the newly created pet attribute or an error
 */
class PetAttributeController : public BNBController
{
public:
    PetAttributeController(QString baseUrl = "/attribute") : BNBController(baseUrl) {};

    void addToResource(const shared_ptr<Resource>);

protected:

    static constexpr const char* ID = "id";

    void getHandler(const shared_ptr<Session> session);
    void postHandler(const shared_ptr<Session> session);

};


#endif // PETATTRIBUTECONTROLLER_H
