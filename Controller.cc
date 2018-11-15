#include "Controller.h"
#include "SmartOpen.h"
#include "View.h"
#include "StringSplitter.h"
#include "StringTrimmer.h"
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
    // fixDesktopSetupInputDelimiters(input);
    bool validApplicationNames = validDesktopSetupInputNames(input);
}

/***************************************
 *            Private Methods          *
 ***************************************/

// void Controller::fixDesktopSetupInputDelimiters(string & input) {
//     bool endsWithCorrectDelimiter = input.substr(input.length() - 2, 2) == View::DESKTOP_DELIMITER;
    
//     if (!endsWithCorrectDelimiter) {
//         input += "||";
//     }
// }

bool Controller::validDesktopSetupInputNames(string input) {
    vector<string> desktops;
    set<string> APPLICATION_NAMES = ScriptService::getApplicationNames();
    StringSplitter::split(desktops, input, View::DESKTOP_DELIMITER);

    for (string desktopText : desktops) {
        StringTrimmer::trim(desktopText);
        vector<string> applications;
        StringSplitter::split(applications, desktopText, View::APPLICATION_DELIMITER);

        for (string applicationName : applications) {
            StringTrimmer::trim(applicationName);
            // TODO: verify that Applications has that app name
            // APPLICATION_NAMES
            if (APPLICATION_NAMES.count(applicationName) == 0) {
                cout << "don't contain " << applicationName << endl;
            } else {
                cout << "you contain " << applicationName << endl;
            }
        }
    }
}