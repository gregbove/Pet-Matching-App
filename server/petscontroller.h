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
 * /pets
 * /pets/{id: a positive integer}
 *
 * > GET /pets/1
 * < a BNBResponse containing a pet
 *
 * > POST /pets
 * | a BNBRequest containing a pet to be created
 * < a BNBResponse containing the newly created pet or an error
 */
class PetsController : public BNBController
{
public:
    PetsController(QString baseUrl = "/pets") : BNBController(baseUrl) {};

    void addToResource(const shared_ptr<Resource>);

protected:
    static constexpr const char* TYPE = "type";
    static constexpr const char* ID = "id";

    void getHandler(const shared_ptr<Session> session);
    void postHandler(const shared_ptr<Session> session);

};

#endif // PETSCONTROLLER_H
