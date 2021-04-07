#ifndef DEFAULTCONTROLLER_H
#define DEFAULTCONTROLLER_H

#include <memory>
#include <restbed>
#include <QJsonObject>
#include <QJsonDocument>

using namespace std;
using namespace restbed;

class DefaultController
{
public:
    DefaultController(string baseUrl = string(""));
    virtual ~DefaultController() {};
    shared_ptr<Resource> getResource();

protected:
    void getIndexHandler(const shared_ptr<Session> session);

private:
    string baseUrl;
};

#endif // DEFAULTCONTROLLER_H
