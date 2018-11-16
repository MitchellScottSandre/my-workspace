#include <iostream>
#include <sstream>      // std::stringstream
#include <istream>      // std::getLine
#include "Desktop.h"
#include "SmartOpen.h"
using namespace std;

struct SmartOpen::SmartOpenImpl {
    Event currentEvent;
    vector<shared_ptr<Desktop>> desktops;

    SmartOpenImpl() : currentEvent{Event()} {}
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
    }
}
   
/**********************************
************** Main  **************
**********************************/

// int main() {
    // const string command = "osascript -e 'tell application \"System Events\" to tell spaces preferences of expose preferences'";
    // const string command = "osascript -e 'tell application \"Finder\" to open the startup disk'";
    // const string command = "find / -type d -name \"Applications\" -maxdepth 1 -exec ls {} \\;";
    // tell application "Finder" to set the position of the front Finder window to {300, 134}
    // const string username = Utils::getStdoutFromCommand("whoami");
    // std::cout << username << std::endl;
    // Utils::getStdoutFromCommand("osascript -e 'tell application \"System Events\" to key code 124 using control down'");
    // SmartOpen * program = new SmartOpen();
    // SmartOpen program;
    // program.run();
    // const vector<string> APPLICATION_NAMES = getApplicationNamesList();
    // const string desiredSetup = getDesktopSetupInput();
    // setupApplications(desiredSetup);
//     return 0;
// }

// int main( int argc, char * argv[] ) {
//     auto app = Gtk::Application::create(argc, argv, "CS 247 Project 2");
//     std::shared_ptr<Model> model = std::make_shared<Model>(0);
//     std::shared_ptr<Controller> controller = std::make_shared<Controller>(model);

//     View gameView(controller, model);
//     model->attach(&gameView);
//     gtk_main();
//     return 0;
// }