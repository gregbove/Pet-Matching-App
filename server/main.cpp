#include <memory>
#include <restbed>

#include "defaultcontroller.h"
#include "userscontroller.h"

using namespace std;
using namespace restbed;

int main(const int, const char**)
{
    shared_ptr<DefaultController> ctlDefault = make_shared<DefaultController>();
    const shared_ptr<Resource> resDefault = make_shared<Resource>();
    ctlDefault->addToResource(resDefault);

    shared_ptr<UsersController> ctlUsers = make_shared<UsersController>();
    const shared_ptr<Resource> resUsers = make_shared<Resource>();
    ctlUsers->addToResource(resUsers);

    auto settings = make_shared<Settings>();
    settings->set_port(1312);
    settings->set_default_header("Connection", "close");

    Service service;
    service.publish(resDefault);
    service.publish(resUsers);

    service.start(settings);

    return EXIT_SUCCESS;
}
