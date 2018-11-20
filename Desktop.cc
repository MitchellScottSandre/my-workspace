#include "Application.h"
#include "DisplayDimensions.h"
#include "Desktop.h"
using namespace std;

struct Desktop::DesktopImpl {
    shared_ptr<Application> app1;
    shared_ptr<Application> app2;

    DesktopImpl(std::shared_ptr<Application> leftApp, std::shared_ptr<Application> rightApp) :
        app1{leftApp}, app2{rightApp} {}
};

Desktop::Desktop(std::shared_ptr<Application> leftApp, std::shared_ptr<Application> rightApp) : 
    desktopPimpl{make_unique<DesktopImpl>(leftApp, rightApp)} {}

Desktop::Desktop(std::shared_ptr<Application> centreApp) : 
    desktopPimpl{make_unique<DesktopImpl>(centreApp, nullptr)} {}

Desktop::~Desktop() {}

void Desktop::setupDesktop() {
    this->desktopPimpl->app1->setupApplication();
    
    if (this->desktopPimpl->app2 != nullptr) {
        this->desktopPimpl->app2->setupApplication();
    }
}

string Desktop::toString() {
    string output = " " + this->desktopPimpl->app1->toString();
    if (this->desktopPimpl->app2 != nullptr) {
        output += " | " + this->desktopPimpl->app2->toString();
    }

    return output;
}
