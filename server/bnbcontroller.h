#ifndef BNBCONTROLLER_H
#define BNBCONTROLLER_H

#include <memory>
#include <restbed>
#include <QString>

using namespace restbed;

class BNBController
{
public:
    BNBController(QString baseUrl);

    virtual void addToResource(const std::shared_ptr<Resource>) = 0;

protected:
    QString baseUrl;
};

#endif // BNBCONTROLLER_H
