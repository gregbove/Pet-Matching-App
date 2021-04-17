#ifndef DEFAULTCONTROLLER_H
#define DEFAULTCONTROLLER_H

#include <memory>
#include <restbed>
#include <QJsonObject>
#include <QJsonDocument>

#include "bnbcontroller.h"

using namespace std;
using namespace restbed;

class DefaultController : public BNBController
{
public:
    DefaultController(QString baseUrl = "") : BNBController(baseUrl) {};

    void addToResource(const shared_ptr<Resource>);

protected:
    void getIndexHandler(const shared_ptr<Session> session);

};

#endif // DEFAULTCONTROLLER_H
