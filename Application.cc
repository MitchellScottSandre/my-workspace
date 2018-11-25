#include <iostream>
#include "DisplayDimensions.h"
#include "Application.h"
#include "ScriptService.h"
using namespace std;

struct Application::ApplicationImpl {
    string name;
    string alternateOpenPhrase;
    ApplicationPosition position;
    DisplayDimensions displayDimensions;
    
    ApplicationImpl(string appName, string alternateOpenPhrase, ApplicationPosition position, DisplayDimensions displayDimensions) :
        name{appName}, 
        alternateOpenPhrase{alternateOpenPhrase == "" ? "New Window" : alternateOpenPhrase}, 
        position{position}, 
        displayDimensions{displayDimensions} { }
};

Application::Application(string appName, string alternateOpenPhrase, ApplicationPosition position, DisplayDimensions displayDimensions) :
    applicationPimpl{make_unique<ApplicationImpl>(appName, alternateOpenPhrase, position, displayDimensions)} {}

Application::~Application() {}

void Application::open() {
    if (ScriptService::isApplicationRunning(this->applicationPimpl->name)) {
        cout << "Application already open" << endl;
        openWithAlternatePhrase();
    } else {
        cout << "Application::open >> normal" << endl;
        string command = "osascript -e 'tell application \"" + this->applicationPimpl->name + "\" \nlaunch \nend tell'";
        ScriptService::executeCommand(command);
    }
}

void Application::openWithAlternatePhrase() {
    string l1 = "tell application \"System Events\"\n";
    string l2 = "tell application process \"Dock\"\n";
    string l3 = "tell list 1\n";
    string l4 = "tell UI element \"" + this->applicationPimpl->name + "\"\n";
    string l5 = "perform action \"AXShowMenu\"\n";
    string l6 = "tell menu\"" + this->applicationPimpl->name + "\"\n";
    string l7 = "tell menu item \"" + this->applicationPimpl->alternateOpenPhrase + "\"\n";
    string l8 = "perform action \"AXPress\"\n";
    string l9 = "end tell\n";
    string l10 = "end tell\n";
    string l11 = "end tell\n";
    string l12 = "end tell\n";
    string l13 = "end tell\n";
    string l14 = "end tell\n";

    string innerCommand = l1 + l2 + l3 + l4 + l5 + l6 + l7 + l8 + l9 + l10 + l11 + l12 + l13 + l14;
    string command = "osascript -e '" + innerCommand + "'";
    cout << innerCommand << endl;
    ScriptService::executeCommand(command);
    ScriptService::delay(1);
}

void Application::putInPosition() {
    string location = "";
    string size = "";
    string halfWidth = to_string(this->applicationPimpl->displayDimensions.getWidth() / 2);
    string height = to_string(this->applicationPimpl->displayDimensions.getHeight());
    string width = to_string(this->applicationPimpl->displayDimensions.getWidth());

    switch (this->applicationPimpl->position) {
        case Application::ApplicationPosition::LEFT:
            location = "{0, 0}";
            size = "{" + halfWidth + ", " + height + "}";
            break;
        case Application::ApplicationPosition::MIDDLE:
            location = "{0, 0}";
            size = "{" + width + ", " + height + "}";
            break;
        case Application::ApplicationPosition::RIGHT:
            location = "{" + halfWidth + ", 0}";
            size = "{" + halfWidth + ", " + height + "}";
            break;
        default:
            break;
    }

    string command1 = "osascript -e 'tell application \"System Events\" to set position of window 1 of application process \"" + this->applicationPimpl->name + "\" to " + location + "'";
    string command2 = "osascript -e 'tell application \"System Events\" to set size of window 1 of application process \"" + this->applicationPimpl->name + "\" to " + size + "'";
    
    ScriptService::executeCommand(command1);
    ScriptService::executeCommand(command2);
    cout << command1 << endl;
    cout << command2 << endl;
}

void Application::bringToFront() {
    string command = "osascript -e 'tell application \"" + this->applicationPimpl->name + "\"to activate'";
    ScriptService::executeCommand(command);
}

void Application::setFullScreen() {
    string command2 = "osascript -e 'tell application \"System Events\" to keystroke \"f\" using {command down, control down}'";
    ScriptService::executeCommand(command2);
}

void Application::setupApplication() {
    if (this->applicationPimpl->position == ApplicationPosition::FULL_SCREEN) {
        open();
        bringToFront();
        ScriptService::delay(2);
        setFullScreen();
    } else {
        open();
        putInPosition();
        bringToFront();

        putInPosition();
        bringToFront();
    }
}

string Application::toString() {
    if (this->applicationPimpl->position == ApplicationPosition::FULL_SCREEN) {
        return "<" + this->applicationPimpl->name + ">";
    }

    return this->applicationPimpl->name;
}
