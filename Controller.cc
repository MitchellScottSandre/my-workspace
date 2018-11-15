#include "Controller.h"
#include "SmartOpen.h"
#include "View.h"
#include "StringUtils.h"
#include "ScriptService.h"
using namespace std;

struct Controller::ControllerImpl {
    shared_ptr<SmartOpen> model;

    ControllerImpl(shared_ptr<SmartOpen> m) : model(m) {}

    ~ControllerImpl() {}
};

Controller::Controller(shared_ptr<SmartOpen> m) : controllerPimpl{make_unique<ControllerImpl>(m)} {}

Controller::~Controller() {}

/***************************************
 *            Public Methods           *
 ***************************************/

void Controller::receivedDesktopSetupInput(string input) {
    // TODO: validDesktopSetupInputDelimiters(input)
    bool validApplicationNames = validDesktopSetupInputNames(input);
}

/***************************************
 *            Private Methods          *
 ***************************************/

bool Controller::validDesktopSetupInputDelimiters(string input) {
    return true;
}

bool Controller::validDesktopSetupInputNames(string input) {
    const set<string> APPLICATION_NAMES = ScriptService::getApplicationNames();

    // Parse input tokens into desktop tokens
    vector<string> desktops;
    StringUtils::split(desktops, input, View::DESKTOP_DELIMITER);

    for (string desktopText : desktops) {
        StringUtils::trim(desktopText);

        // Parse desktop tokens into applicationName tokens
        vector<string> applications;
        StringUtils::split(applications, desktopText, View::APPLICATION_DELIMITER);

        // Check if application exists
        for (string applicationName : applications) {
            StringUtils::trim(applicationName);
            if (APPLICATION_NAMES.count(StringUtils::str_tolower(applicationName)) == 0) {
                Event event = Event(Event::EventType::INPUT_ERROR, Event::EventError::BAD_APPLICATION_NAME, applicationName);
                this->controllerPimpl->model->emitEvent(event);
                return false;
            } 
        }
    }

    return true;
}