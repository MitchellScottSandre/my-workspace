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

View::View(shared_ptr<Controller> c, shared_ptr<SmartOpen> m) : viewPimpl{make_unique<ViewImpl>(c, m)} {}

View::~View() {}

void View::getNotified() {
    const Event e = viewPimpl->model->getLastEvent();

    switch (e.type) {
        case Event::EventType::DISPLAY_WELCOME:
            displayWelcome();
            break;
        case Event::EventType::GET_DESKTOP_SETUP_INPUT:
            getDesktopSetupInput();
            break;
        case Event::EventType::ERROR:
            displayError(e.error, e.data);
            break;
        default:
            return;
    }
}

//

void View::displayWelcome() {
    cout << endl;
    cout << "displayWelcome" << endl;
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

void View::displayError(Event::EventError error, string errorMessage) {
    string output = "";
    switch(error) {
        case Event::EventError::BAD_APPLICATION_NAME:
            output = "Invalid Application Name: " + errorMessage;
            break;
        default:
            return;
    }

    cerr << "Error: " + output << endl;
}