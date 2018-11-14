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

            break;
        default:

    }
}