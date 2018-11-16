#include <iostream>
#include "DisplayDimensions.h"
#include "Application.h"
#include "ScriptService.h"
using namespace std;

struct Application::ApplicationImpl {
    string name;
    ApplicationPosition position;
    DisplayDimensions displayDimensions;

    ApplicationImpl(string appName, ApplicationPosition position, DisplayDimensions displayDimensions) :
        name{appName}, position{position}, displayDimensions{displayDimensions} {}
};

Application::Application(string appName, ApplicationPosition position, DisplayDimensions displayDimensions) :
    applicationPimpl{make_unique<ApplicationImpl>(appName, position, displayDimensions)} {}

Application::~Application() {}

void Application::open() {
    string command = "osascript -e 'tell application \"" + this->applicationPimpl->name + "\" \nlaunch \nend tell'";
    ScriptService::executeCommand(command);
}

void Application::putInPosition() {
    string loation = "";
    string size = "";
    string halfWidth = to_string(this->applicationPimpl->displayDimensions.getWidth() / 2);
    string height = to_string(this->applicationPimpl->displayDimensions.getHeight());
    string width = to_string(this->applicationPimpl->displayDimensions.getWidth());

    switch (this->applicationPimpl->position) {
        case Application::ApplicationPosition::LEFT:
            loation = "{0, 0}";
            size = "{" + halfWidth + ", " + height + "}";
            break;
        case Application::ApplicationPosition::MIDDLE:
            loation = "{0, 0}";
            size = "{" + width + ", " + height + "}";
            break;
        case Application::ApplicationPosition::RIGHT:
            loation = "{" + halfWidth + ", 0}";
            size = "{" + halfWidth + ", " + height + "}";
            break;
    }

    string command1 = "osascript -e 'tell application \"System Events\" to set position of window 1 of application process \"" + this->applicationPimpl->name + "\" to " + loation + "'";
    string command2 = "osascript -e 'tell application \"System Events\" to set size of window 1 of application process \"" + this->applicationPimpl->name + "\" to " + size + "'";

    cout << command1 << endl;
    cout << command2 << endl;
    ScriptService::executeCommand(command1);
    ScriptService::executeCommand(command2);
}

void Application::setupApplication() {
    open();
    putInPosition();
}
