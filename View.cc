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

View::View(shared_ptr<Controller> c, shared_ptr<SmartOpen> m) : viewPimpl{make_unique<ViewImpl>(c, m)} {}

View::~View() {}

void View::getNotified() {
    const Event e = viewPimpl->model->getLastEvent();

    switch (e.eventType) {
        case Event::EventType::DISPLAY_WELCOME:
            displayWelcome();
            break;
        case Event::EventType::GET_DESKTOP_SETUP_INPUT:
            getDesktopSetupInput();
            break;
        default:
            throw;
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

    viewPimpl->controller->didGetDesktopSetupInput(input);
}