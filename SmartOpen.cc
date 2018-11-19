#include <iostream>
#include <sstream>      
#include <istream>      
#include "Desktop.h"
#include "SmartOpen.h"
#include "ScriptService.h"
#include "DisplayDimensions.h"
using namespace std;

struct SmartOpen::SmartOpenImpl {
    Event currentEvent;
    vector<shared_ptr<Desktop>> desktops;
    const set<string> APPLICATION_NAMES;
    const DisplayDimensions DISPLAY_DIMENSIONS; 

    SmartOpenImpl() : 
        currentEvent{Event()}, 
        APPLICATION_NAMES{ScriptService::getApplicationNames()}, 
        DISPLAY_DIMENSIONS{ScriptService::getDisplayDimensions()} {}
};

SmartOpen::SmartOpen() : smartOpenPimpl{make_unique<SmartOpenImpl>()} {}

SmartOpen::~SmartOpen() {}

void SmartOpen::run() {
    emitEvent(Event::EventType::DISPLAY_WELCOME);
    emitEvent(Event::EventType::GET_DESKTOP_SETUP_INPUT);
}

void SmartOpen::emitEvent(Event e) {
    this->smartOpenPimpl->currentEvent = e;
    this->notifyObservers();
}

void SmartOpen::emitError(Event::EventError e, string errorMessage) {
    emitEvent(Event(Event::EventType::ERROR, e, errorMessage));
}

Event SmartOpen::getLastEvent() {
    return this->smartOpenPimpl->currentEvent;
}

void SmartOpen::setDesktops(vector<shared_ptr<Desktop>> desktops) {
    this->smartOpenPimpl->desktops = desktops;
}

void SmartOpen::setupWorkspace() {
    for (int i = 0; i < this->smartOpenPimpl->desktops.size(); i++) {
        shared_ptr<Desktop> desktop = this->smartOpenPimpl->desktops.at(i);
        desktop->setupDesktop();
        ScriptService::switchDesktops(ScriptService::DesktopDirection::RIGHT);
    }
}

set<string> SmartOpen::getApplicationNames() {
    return this->smartOpenPimpl->APPLICATION_NAMES;
}

DisplayDimensions SmartOpen::getDisplayDimensions() {
    return this->smartOpenPimpl->DISPLAY_DIMENSIONS;
}