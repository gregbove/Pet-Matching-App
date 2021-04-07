#include <memory>
#include <restbed>

#include "defaultcontroller.h"

using namespace std;
using namespace restbed;

int main(const int, const char**)
{
    shared_ptr<DefaultController> ctlDefault = make_shared<DefaultController>();
    const shared_ptr<Resource> resDefault = ctlDefault->getResource();

    auto settings = make_shared<Settings>();
    settings->set_port(1312);
    settings->set_default_header("Connection", "close");

    Service service;
    service.publish(resDefault);
    service.start(settings);

    return EXIT_SUCCESS;
}
