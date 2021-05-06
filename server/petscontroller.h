#ifndef PETSCONTROLLER_H
#define PETSCONTROLLER_H


#include "../common/bnbresponse.h"
#include "../common/bnbrequest.h"
#include "../common/pet.h"

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
 * @brief Handles fetching and creating different types of Users
 *
 * Endpoints:
 * /pet/{type: dog|cat|snake}
 * /pet/{name: a string type for name of pet}
 *
 * > GET /pet/dog
 * < a BNBResponse containing a list of Dogs
 *
 * > POST /pet/dog
 * | a BNBRequest containing a dog to be created
 * < a BNBResponse containing the newly created dog or an error
 */
class PetsController : public BNBController
{
public:
    PetsController(QString baseUrl = "/pet") : BNBController(baseUrl) {};

    void addToResource(const shared_ptr<Resource>);

protected:
    static constexpr const char* TYPE = "type";
    static constexpr const char* ID = "id";

    void getHandler(const shared_ptr<Session> session);
    void postHandler(const shared_ptr<Session> session);

};

#endif // PETSCONTROLLER_H
