#include <iostream>
#include <sstream>      
#include <istream>      
#include "Desktop.h"
#include "SmartOpen.h"
#include "ScriptService.h"
#include "DisplayDimensions.h"
#include "FileService.h"
using namespace std;

struct SmartOpen::SmartOpenImpl {
    Event currentEvent;
    vector<shared_ptr<Desktop>> desktops;
    const vector<string> APPLICATION_NAMES; 
    const vector<string> SAVED_WORKSPACES;
    const map<string, string> ALTERNATE_OPEN_PHRASES;
    const map<string, string> ALIASES;
    const map<string, string> PROCESS_NAMES;
    const DisplayDimensions DISPLAY_DIMENSIONS; 

    SmartOpenImpl() : 
        currentEvent{Event()}, 
        APPLICATION_NAMES{ScriptService::getApplicationNames()},
        SAVED_WORKSPACES{FileService::readWorkspaces()},
        ALTERNATE_OPEN_PHRASES{FileService::readOpenPhrases()},
        ALIASES{FileService::readAliases()},
        PROCESS_NAMES{FileService::readProcessNames()},
        DISPLAY_DIMENSIONS{ScriptService::getDisplayDimensions()} {}
};

/***************************************
 *            Private Methods          *
 ***************************************/

bool SmartOpen::workspaceAlreadyExists(string workspace) {
    for (string w : this->smartOpenPimpl->SAVED_WORKSPACES) {
        if (w == workspace) {
            return true;
        }
    }

    return false;
}

/***************************************
 *            Public Methods           *
 ***************************************/

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

    if (!workspaceAlreadyExists(workspaceText)) {
        FileService::createWorkspace(workspaceText);
    }
}

/***************************************
 *        Accessors / Mutators         *
 ***************************************/

void SmartOpen::setDesktops(vector<shared_ptr<Desktop>> desktops) {
    this->smartOpenPimpl->desktops = desktops;
}

Event SmartOpen::getLastEvent() {
    return this->smartOpenPimpl->currentEvent;
}

vector<string> SmartOpen::getApplicationNames() {
    return this->smartOpenPimpl->APPLICATION_NAMES;
}

vector<string> SmartOpen::getExistingWorkspaces() {
    return this->smartOpenPimpl->SAVED_WORKSPACES;
}

map<string, string> SmartOpen::getAlternateOpenPhrases() {
    return this->smartOpenPimpl->ALTERNATE_OPEN_PHRASES;
}

map<string, string> SmartOpen::getAliases() {
    return this->smartOpenPimpl->ALIASES;
}

map<string, string> SmartOpen::getProcessNames() {
    return this->smartOpenPimpl->PROCESS_NAMES;
}

DisplayDimensions SmartOpen::getDisplayDimensions() {
    return this->smartOpenPimpl->DISPLAY_DIMENSIONS;
}