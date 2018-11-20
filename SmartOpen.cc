#include <iostream>
#include <sstream>      
#include <istream>      
#include "Desktop.h"
#include "SmartOpen.h"
#include "ScriptService.h"
#include "DisplayDimensions.h"
#include "FileService.h"
#include "Alias.h"
using namespace std;

struct SmartOpen::SmartOpenImpl {
    Event currentEvent;
    vector<shared_ptr<Desktop>> desktops;
    const vector<string> APPLICATION_NAMES; 
    const vector<shared_ptr<Alias>> APPLICATION_ALIASES;
    const DisplayDimensions DISPLAY_DIMENSIONS; 

    SmartOpenImpl() : 
        currentEvent{Event()}, 
        APPLICATION_NAMES{ScriptService::getApplicationNames()}, 
        APPLICATION_ALIASES{FileService::readAliases()},
        DISPLAY_DIMENSIONS{ScriptService::getDisplayDimensions()} {}
};

SmartOpen::SmartOpen() : smartOpenPimpl{make_unique<SmartOpenImpl>()} {}

SmartOpen::~SmartOpen() {}

void SmartOpen::run() {
    emitEvent(Event::EventType::DISPLAY_WELCOME);
    emitEvent(Event::EventType::GET_MENU_INPUT);
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

        if (i < this->smartOpenPimpl->desktops.size() - 1) {
            ScriptService::switchDesktops(ScriptService::DesktopDirection::RIGHT);
        }
    }
}

void SmartOpen::saveWorkspace() {
    string workspaceText = "";
    for (int i = 0; i < this->smartOpenPimpl->desktops.size(); ++i) {
        workspaceText += this->smartOpenPimpl->desktops.at(i)->toString() + " ||";
    }
    FileService::createWorkspace(workspaceText);
}

vector<string> SmartOpen::getApplicationNames() {
    return this->smartOpenPimpl->APPLICATION_NAMES;
}

DisplayDimensions SmartOpen::getDisplayDimensions() {
    return this->smartOpenPimpl->DISPLAY_DIMENSIONS;
}

vector<shared_ptr<Alias>> SmartOpen::getAliases() {
    return this->smartOpenPimpl->APPLICATION_ALIASES;
}