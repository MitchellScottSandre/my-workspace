#include <iostream>
#include <sstream>      // std::stringstream
#include <istream>      // std::getLine
#include "Desktop.h"
#include "SmartOpen.h"
// #include "Utils.cc"
using namespace std;

struct SmartOpen::SmartOpenImpl {
    vector<string> APPLICATION_NAMES;
    string desiredSetup;

    // SmartOpenImpl() : APPLICATION_NAMES{Utils::getApplicationNamesList()} {}
    SmartOpenImpl() {}
};

SmartOpen::SmartOpen() : smartOpenPimpl{make_unique<SmartOpenImpl>()} {}

SmartOpen::~SmartOpen() {}

void SmartOpen::run() {
    
}

Event SmartOpen::getLastEvent() {
    return Event(Event::EventType::DISPLAY_WELCOME);
}
   

//     SmartOpen() : APPLICATION_NAMES{Utils::getApplicationNamesList()} {}

//     string getSetupInput() {
//         cout << "Enter desired desktop(s) setup." << endl;
//         cout << "Format: " << endl;
//         cout << "DESK_1_LEFT_APP | DESK_1_RIGHT_APP || DESK_2_MIDDLE_APP || <FULL_SCREEN_APP> || ..." << endl;
//         string input;
//         getline(cin, input);

//         bool endsWithCorrectDelimiter = input.substr(input.length() - 2, 2) == "||";
        
//         if (!endsWithCorrectDelimiter) {
//             input += "||";
//         }

//         return input;
//     }

//     void setupApplications(const string desiredSetup) {
//         vector<Desktop> desktops = Desktop::getDesktopsFromInput(desiredSetup);
//         DisplayDimensions displayDimensions = Utils::getDisplayDimensions();
//         // Navigate all the way to the left
//         Desktop::switchDesktop(Desktop::DIRECTION_LEFT);

//         for (int i = 0; i < desktops.size(); i++ ) {
//             desktops.at(i).setupApplications(displayDimensions);
//             Desktop::switchDesktop(Desktop::DIRECTION_RIGHT);
//         }
//     }

//     void run() {
//         this->desiredSetup = getSetupInput();
//         setupApplications(this->desiredSetup);
//     }

// };

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