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

void Controller::receivedDesktopSetupInput(const string input) {
    bool validDelimiters = validDesktopSetupInputDelimiters(input);
    bool validAppNames = validDesktopSetupInputNames(input);

    if (validDelimiters && validAppNames) {
        // TODO: call mode
    } else {
        this->controllerPimpl->model->emitEvent(Event(Event::EventType::GET_DESKTOP_SETUP_INPUT));
    }
}

/***************************************
 *            Private Methods          *
 ***************************************/

bool Controller::validDesktopSetupInputDelimiters(const string input) {
    // TODO: 
    return true;
}

bool Controller::validDesktopSetupInputNames(const string input) {
    const set<string> APPLICATION_NAMES = ScriptService::getApplicationNames();

    // Parse input tokens into desktop tokens
    // TODO: generate Desktop objects here. Set them in the model if validation is successful
    vector<string> desktops;
    StringUtils::split(desktops, input, View::DESKTOP_DELIMITER);

    for (string desktopText : desktops) {
        StringUtils::trim(desktopText);

        // Parse desktop tokens into applicationName tokens
        vector<string> applications;
        StringUtils::split(applications, desktopText, View::APPLICATION_DELIMITER);

        // Check if applicationName exists 
        for (string applicationName : applications) {
            StringUtils::trim(applicationName);

            bool appNameExists = false;
            for (auto it = APPLICATION_NAMES.begin(); it != APPLICATION_NAMES.end(); ++it) {
                string s = *it;
                if (StringUtils::str_tolower(s) == StringUtils::str_tolower(applicationName)) {
                    appNameExists = true;
                    break;
                }
            }

            if (!appNameExists) {
                Event event = Event(Event::EventType::ERROR, Event::EventError::BAD_APPLICATION_NAME, applicationName);
                this->controllerPimpl->model->emitEvent(event);
                return false;
            } 
        }
    }

    return true;
}