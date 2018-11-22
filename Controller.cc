#include <map>
#include "Controller.h"
#include "SmartOpen.h"
#include "View.h"
#include "StringUtils.h"
#include "ScriptService.h"
#include "DisplayDimensions.h"
#include "Desktop.h"
#include "Application.h"
using namespace std;

const string Controller::NULL_APP_NAME = "NULL_APP_NAME";

struct Controller::ControllerImpl {
    shared_ptr<SmartOpen> model;

    ControllerImpl(shared_ptr<SmartOpen> m) : model(m) {}

    ~ControllerImpl() {}
};

/***************************************
 *            Public Methods           *
 ***************************************/

Controller::Controller(shared_ptr<SmartOpen> m) : controllerPimpl{make_unique<ControllerImpl>(m)} {}

Controller::~Controller() {}

void Controller::receivedMenuInput(string input) {
    bool validMenuInput = validNumberInput(input, 1, 2);

    if (validMenuInput == VALID) {
        Event::EventType event = input == "1" ? Event::EventType::GET_DESKTOP_SETUP_INPUT : Event::EventType::GET_EXISTING_WORKSPACE_INPUT;
        this->controllerPimpl->model->emitEvent(event);
    } else {
        this->controllerPimpl->model->emitEvent(Event::EventType::GET_MENU_INPUT);
    }
}

void Controller::parseWorkspaceInput(string input, bool isExistingWorkspace) {
    bool validDesktopSetup = validDesktopSetupInput(input);

    if (validDesktopSetup == VALID) {
        this->controllerPimpl->model->setupWorkspace();
        if (!isExistingWorkspace) {
            this->controllerPimpl->model->emitEvent(Event::EventType::ASK_TO_SAVE_WORKSPACE);
        }
    } else {
        this->controllerPimpl->model->emitEvent(Event(Event::EventType::GET_MENU_INPUT));
    }
}

void Controller::receivedSaveWorkspaceMenuInput(string input) {
    bool validSaveInput = validNumberInput(input, 1, 2);

    if (validSaveInput == VALID) {
        this->controllerPimpl->model->saveWorkspace();
    } else {
        this->controllerPimpl->model->emitEvent(Event::EventType::ASK_TO_SAVE_WORKSPACE);
    }
}

void Controller::receivedLoadExistingWorkspaceInput(string input) {
    const int numberExistingWorkspaces = this->controllerPimpl->model->getExistingWorkspaces().size();
    bool validExistingWorkspaceInput = validNumberInput(input, 0, numberExistingWorkspaces - 1);

    if (validExistingWorkspaceInput == VALID) {
        int inputValue = stoi(input);
        parseWorkspaceInput(this->controllerPimpl->model->getExistingWorkspaces().at(inputValue), true);
    } else {
        this->controllerPimpl->model->emitEvent(Event::GET_EXISTING_WORKSPACE_INPUT);
    }
}
/***************************************
 *            Private Methods          *
 ***************************************/

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
                desktops.emplace_back(make_shared<Desktop>(applications.at(Application::LEFT_INDEX)));
            } else if (applications.size() == 2) {
                desktops.emplace_back(make_shared<Desktop>(applications.at(Application::LEFT_INDEX), applications.at(Application::RIGHT_INDEX)));
            }
        } else {
            return ERROR;
        }
    }

    return VALID;
}

bool Controller::parseApplicationTokens(vector<shared_ptr<Application>> & applications, string desktopToken) {
    vector<string> applicationTokens;
    StringUtils::split(applicationTokens, desktopToken, View::APPLICATION_DELIMITER);

    if (applicationTokens.size() > 2) {
        this->controllerPimpl->model->emitError(Event::EventError::TOO_MANY_APPLICATIONS);
        return ERROR;
    }

    for (int i = 0; i < applicationTokens.size(); i++) {
        bool appIsFullScreen = false;
        string applicationToken = applicationTokens.at(i);
        string systemApplicationName;
        StringUtils::trim(applicationToken);

        if (validFullScreenDelimiter(applicationToken, appIsFullScreen, i) == ERROR) {
            return ERROR;
        }

        systemApplicationName = getSystemApplicationName(applicationToken);

        if (systemApplicationName == NULL_APP_NAME) {
            this->controllerPimpl->model->emitError(Event::EventError::INVALID_APPLICATION_NAME, applicationToken);
            return ERROR;
        }

        applications.emplace_back(createApplication(systemApplicationName, appIsFullScreen, applicationTokens.size(), i));
    }

    return VALID;
}

bool Controller::validFullScreenDelimiter(string & applicationToken, bool & appIsFullScreen, const int tokenIndex) {
    if (applicationToken.at(0) == View::FULL_SCREEN_LEFT_DELIMITER && applicationToken.at(applicationToken.length() - 1) == View::FULL_SCREEN_RIGHT_DELIMITER) {
        if (tokenIndex != 0) {
            this->controllerPimpl->model->emitError(Event::EventError::INVALID_FULLSCREEN, applicationToken);
            return ERROR;
        }

        appIsFullScreen = true;
        StringUtils::removeFullScreenDelimiters(applicationToken);
    }
    return VALID;
}

string Controller::getSystemApplicationName(string applicationToken) {
    const vector<string> APPLICATION_NAMES = this->controllerPimpl->model->getApplicationNames();

    for (auto it = APPLICATION_NAMES.begin(); it != APPLICATION_NAMES.end(); ++it) {
        const string SYSTEM_APP_NAME = *it;
        if (StringUtils::str_tolower(SYSTEM_APP_NAME) == StringUtils::str_tolower(applicationToken)) {
            return SYSTEM_APP_NAME;
        }
    }

    const map<string, string> ALIASES = this->controllerPimpl->model->getAliases();

    auto it = ALIASES.find(StringUtils::str_tolower(applicationToken));

    if (it != ALIASES.end()) {
        return it->second;
    }

    return NULL_APP_NAME;
}

shared_ptr<Application> Controller::createApplication(string systemAppName, bool fullScreen, int numTokensInDesktop, int tokenIndex) {
    if (numTokensInDesktop == 1) {
        Application::ApplicationPosition position = fullScreen ? Application::ApplicationPosition::FULL_SCREEN : Application::ApplicationPosition::MIDDLE;
        return make_shared<Application>(systemAppName, position, this->controllerPimpl->model->getDisplayDimensions());
    } else {
        if (tokenIndex == Application::LEFT_INDEX) {
            return make_shared<Application>(systemAppName, Application::ApplicationPosition::LEFT, this->controllerPimpl->model->getDisplayDimensions());
        } else {
            return make_shared<Application>(systemAppName, Application::ApplicationPosition::RIGHT, this->controllerPimpl->model->getDisplayDimensions());
        }
    }
}

// TODO: should use a map. need to delete alias as well. need to be able to parse the ["":""] text too
string Controller::getAlternateApplicationOpenPhrase(string systemAppName) {
    map<string, string> ALTERNATE_OPEN_PHRASES = this->controllerPimpl->model->getAlternateOpenPhrases();
    
}

bool Controller::validNumberInput(string input, int min, int max) {
    bool parsedInput = false;
    int inputValue = -1;
    try {
        inputValue = stoi(input);
        parsedInput = true;
    } catch (...) {}

    bool validNumber = false;
    
    if (parsedInput) {
        validNumber = inputValue >= min && inputValue <= max;
    }

    if (!parsedInput || !validNumber) {
        this->controllerPimpl->model->emitError(Event::EventError::INVALID_NUMBER_INPUT);
        return ERROR;
    }
    
    return VALID;
}