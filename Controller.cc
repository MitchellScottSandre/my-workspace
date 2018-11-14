#include "Controller.h"
#include "SmartOpen.h"
#include "View.h"
using namespace std;

struct Controller::ControllerImpl {
    shared_ptr<SmartOpen> model;

    ControllerImpl(shared_ptr<SmartOpen> m) : model(m) {}

    ~ControllerImpl() {}
};

Controller::Controller(shared_ptr<SmartOpen> m) : controllerPimpl{make_unique<ControllerImpl>(m)} {}

Controller::~Controller() {}

void Controller::didGetDesktopSetupInput(string input) {
    bool endsWithCorrectDelimiter = input.substr(input.length() - 2, 2) == "||";
    
    if (!endsWithCorrectDelimiter) {
        input += "||";
    }
}