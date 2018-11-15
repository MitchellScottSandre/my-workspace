#include "Controller.h"
#include "SmartOpen.h"
#include "View.h"
#include "StringUtils.h"
#include "ScriptService.h"
#include "Desktop.h"
#include "Application.h"
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
    // bool validDelimiters = validDesktopSetupInputDelimiters(input);
    bool validAppNames = validDesktopSetupInput(input);

    if (validAppNames) {
        // TODO: call mode
    } else {
        this->controllerPimpl->model->emitEvent(Event(Event::EventType::GET_DESKTOP_SETUP_INPUT));
    }
}

/***************************************
 *            Private Methods          *
 ***************************************/

// bool Controller::validDesktopSetupInputDelimiters(const string input) {
//     // TODO: delete this?
//     return true;
// }

bool Controller::validDesktopSetupInput(const string input) {
    const set<string> APPLICATION_NAMES = ScriptService::getApplicationNames();

    // Parse input tokens into desktop tokens
    // TODO: generate Desktop objects here. Set them in the model if validation is successful
    vector<string> desktopTokens;
    vector<Desktop> desktops;
    StringUtils::split(desktopTokens, input, View::DESKTOP_DELIMITER);

    for (string desktopToken : desktopTokens) {
        StringUtils::trim(desktopToken);

        // Parse desktop tokens into applicationName tokens
        vector<string> applicationTokens;
        vector<shared_ptr<Application>> applications;
        StringUtils::split(applicationTokens, desktopToken, View::APPLICATION_DELIMITER);

        if (applicationTokens.size() > 2) {
            this->controllerPimpl->model->emitError(Event::EventError::TOO_MANY_APPLICATIONS);
            return false;
        }

        bool appIsFullScreen = false;

        // Check if applicationName exists in Applications Folder
        for (int i = 0; i < applicationTokens.size(); i++) {

            string applicationToken = applicationTokens.at(i);
            StringUtils::trim(applicationToken);

            if (applicationToken.at(0) == View::FULL_SCREEN_LEFT_DELIMITER && applicationToken.at(applicationToken.length() - 1) == View::FULL_SCREEN_RIGHT_DELIMITER) {
                appIsFullScreen = true;
                StringUtils::removeFullScreenDelimiters(applicationToken);
                if (i != 0) {
                    this->controllerPimpl->model->emitError(Event::EventError::INVALID_FULLSCREEN, applicationToken);
                    return false;
                }
            }

            bool appNameExists = false;
            for (auto it = APPLICATION_NAMES.begin(); it != APPLICATION_NAMES.end(); ++it) {
                string s = *it;
                if (StringUtils::str_tolower(s) == StringUtils::str_tolower(applicationToken)) {
                    appNameExists = true;
                    break;
                }
            }

            if (!appNameExists) {
                this->controllerPimpl->model->emitError(Event::EventError::BAD_APPLICATION_NAME, applicationToken);
                return false;
            }

            if (applicationTokens.size() == 1) {
                // TODO: create desktop using displaydimension
                // desktops.emplace_back(Desktop(make_shared<Application>(applicationToken, Application::ApplicationPosition::MIDDLE)));
            }
        }
    }

    return true;
}