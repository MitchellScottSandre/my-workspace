#include <iostream>
#include "View.h"
#include "Controller.h"
#include "SmartOpen.h"
#include "Event.h"
using namespace std;

struct View::ViewImpl {
    shared_ptr<Controller> controller;
    shared_ptr<SmartOpen> model;

    ViewImpl(shared_ptr<Controller> c, shared_ptr<SmartOpen> m) : controller(c), model(m) {}

    ~ViewImpl() {}
};

const string View::DESKTOP_DELIMITER = "||";
const string View::APPLICATION_DELIMITER = "|";
const char View::FULL_SCREEN_LEFT_DELIMITER = '<';
const char View::FULL_SCREEN_RIGHT_DELIMITER = '>';

View::View(shared_ptr<Controller> c, shared_ptr<SmartOpen> m) : viewPimpl{make_unique<ViewImpl>(c, m)} {}

View::~View() {}

void View::getNotified() {
    const Event e = viewPimpl->model->getLastEvent();

    switch (e.type) {
        case Event::EventType::DISPLAY_WELCOME:
            displayWelcome();
            break;
        case Event::EventType::GET_MENU_INPUT:
            getMenuInput();
            break;
        case Event::EventType::GET_DESKTOP_SETUP_INPUT:
            getDesktopSetupInput();
            break;
        case Event::EventType::GET_EXISTING_WORKSPACE_INPUT:
            getExistingWorkspaceInput();
        case Event::EventType::ERROR:
            displayError(e.error, e.data);
            break;
        default:
            return;
    }
}

void View::displayWelcome() {
    cout << "displayWelcome" << endl;
}

void View::getMenuInput() {
    cout << endl;
    cout << "Press 1 to open a new Workspace." << endl;
    cout << "Press 2 to load an existing Workspace." << endl;

    string input;
    cin >> input;

    viewPimpl->controller->receivedMenuInput(input);
}

void View::getDesktopSetupInput() {
    cout << endl;
    cout << "Enter desired desktop(s) setup." << endl;
    cout << "Format: DESK_1_APP(s) || DESK_2_APP(s) || ..." << endl;
    cout << "Apps Format: APP_LEFT | APP_RIGHT    OR    APP_CENTRE    OR    <APP_FULL_SCREEN>" << endl;

    string input;
    getline(cin, input);

    viewPimpl->controller->receivedDesktopSetupInput(input);
}

void View::getExistingWorkspaceInput() {

}

void View::displayError(Event::EventError error, string errorMessage) {
    string output = "";
    switch(error) {
        case Event::EventError::BAD_MENU_INPUT:
            output = "Invalid menu input: " + errorMessage;
            break;
        case Event::EventError::BAD_APPLICATION_NAME:
            output = "Invalid Application Name: " + errorMessage;
            break;
        case Event::EventError::TOO_MANY_APPLICATIONS:
            output = "Can't have more than 2 applications per desktop";
            break;
        case Event::EventError::INVALID_FULLSCREEN:
            output = "Can't have another application open with " + errorMessage + " in full screen";
            break;
        default:
            return;
    }

    cerr << "Error: " + output << endl;
}