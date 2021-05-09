#ifndef MATCHESCONTROLLER_H
#define MATCHESCONTROLLER_H

#include "../common/bnbresponse.h"
#include "../common/bnbrequest.h"
#include "../common/petmatch.h"

#include "bnbcontroller.h"
#include "db.h"

#include <memory>
#include <restbed>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

using namespace std;
using namespace restbed;

class MatchesController : public BNBController
{
public:
    MatchesController(QString baseUrl = "/matches") : BNBController(baseUrl) {};

    void addToResource(const shared_ptr<Resource>);

protected:
    static constexpr const char* ID_PATH_PARAM = "parentId";

    void getHandler(const shared_ptr<Session> session);
    void postHandler(const shared_ptr<Session> session);
};

#endif // MATCHESCONTROLLER_H
