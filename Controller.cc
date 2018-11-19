#include "Controller.h"
#include "SmartOpen.h"
#include "View.h"
#include "StringUtils.h"
#include "ScriptService.h"
#include "DisplayDimensions.h"
#include "Desktop.h"
#include "Application.h"
using namespace std;

// const bool Controller::VALID = true;

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
    bool validDesktopSetup = validDesktopSetupInput(input);

    if (validDesktopSetup == VALID) {
        this->controllerPimpl->model->setupWorkspace();
    } else {
        this->controllerPimpl->model->emitEvent(Event(Event::EventType::GET_DESKTOP_SETUP_INPUT));
    }
}

/***************************************
 *            Private Methods          *
 ***************************************/

// TODO: refactor this function
bool Controller::validDesktopSetupInput(const string input) {
    vector<shared_ptr<Desktop>> desktops;
    if (parseDesktopTokens(desktops, input) == VALID) {
        controllerPimpl->model->setDesktops(desktops);
        return VALID;
    }
    return ERROR;
}

bool Controller::parseDesktopTokens(vector<shared_ptr<Desktop>> & desktops, const string input) {
    vector<string> desktopTokens;
    StringUtils::split(desktopTokens, input, View::DESKTOP_DELIMITER);

    for (string desktopToken : desktopTokens) {
        vector<shared_ptr<Application>> applications;
        StringUtils::trim(desktopToken);

        if (parseApplicationTokens(applications, desktopToken) == VALID) {
            if (applications.size() == 1) {
                desktops.emplace_back(make_shared<Desktop>(applications.at(0)));
            } else if (applications.size() == 2) {
                desktops.emplace_back(make_shared<Desktop>(applications.at(0), applications.at(1)));
            }
        } else {
            return ERROR;
        }
    }
}

bool Controller::parseApplicationTokens(vector<shared_ptr<Application>> & applications, string desktopToken) {
    vector<string> applicationTokens;
    StringUtils::split(applicationTokens, desktopToken, View::APPLICATION_DELIMITER);

    if (applicationTokens.size() > 2) {
        this->controllerPimpl->model->emitError(Event::EventError::TOO_MANY_APPLICATIONS);
        return ERROR;
    }

    bool appIsFullScreen = false;

    // Check if applicationName exists in Applications Folder
    for (int i = 0; i < applicationTokens.size(); i++) {
        string applicationToken = applicationTokens.at(i);
        string systemApplicationName;
        StringUtils::trim(applicationToken);

        if (applicationToken.at(0) == View::FULL_SCREEN_LEFT_DELIMITER && applicationToken.at(applicationToken.length() - 1) == View::FULL_SCREEN_RIGHT_DELIMITER) {
            appIsFullScreen = true;
            StringUtils::removeFullScreenDelimiters(applicationToken);
            if (i != 0) {
                this->controllerPimpl->model->emitError(Event::EventError::INVALID_FULLSCREEN, applicationToken);
                return ERROR;
            }
        }

        bool appNameExists = false;
        for (auto it = APPLICATION_NAMES.begin(); it != APPLICATION_NAMES.end(); ++it) {
            const string SYSTEM_APP_NAME = *it;
            if (StringUtils::str_tolower(SYSTEM_APP_NAME) == StringUtils::str_tolower(applicationToken)) {
                appNameExists = true;
                systemApplicationName = SYSTEM_APP_NAME;
                break;
            }
        }

        if (!appNameExists) {
            this->controllerPimpl->model->emitError(Event::EventError::BAD_APPLICATION_NAME, applicationToken);
            return ERROR;
        }

        shared_ptr<Application> application;

        if (applicationTokens.size() == 1) {
            Application::ApplicationPosition position = appIsFullScreen ? Application::ApplicationPosition::FULL_SCREEN : Application::ApplicationPosition::MIDDLE;
            application = make_shared<Application>(systemApplicationName, position, this->controllerPimpl->model->getDisplayDimensions());
        } else {
            if (i == 0) {
                application = make_shared<Application>(systemApplicationName, Application::ApplicationPosition::LEFT, this->controllerPimpl->model->getDisplayDimensions());
            } else {
                application = make_shared<Application>(systemApplicationName, Application::ApplicationPosition::RIGHT, this->controllerPimpl->model->getDisplayDimensions());
            }
        }

        applications.emplace_back(application);
    }
}