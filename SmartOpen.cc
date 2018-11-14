#include <iostream>
#include <vector>
#include <sstream>      // std::stringstream
#include <istream>      // std::getLine
#include <string>
#include "Desktop.cc"
using namespace std;

class SmartOpen {
private:
    vector<string> APPLICATION_NAMES;
    string desiredWorkspaceSetup;

public:
    SmartOpen() : APPLICATION_NAMES{Utils::getApplicationNamesList()} {}

    string getDesktopSetupInput() {
        cout << "Enter desired desktop(s) setup." << endl;
        cout << "Format: DESK_1_APP_1 | DESK_1_APP_2 || DESK_2_APP_1 | DESK_2_APP_2 || ..." << endl;

        string input;
        getline(cin, input);

        bool endsWithCorrectDelimiter = input.substr(input.length() - 2, 2) == "||";
        
        if (!endsWithCorrectDelimiter) {
            input += "||";
        }

        return input;
    }

    void setupApplications(const string desiredSetup) {
        vector<Desktop> desktops = Desktop::getDesktopsFromInput(desiredSetup);
        DisplayDimensions displayDimensions = Utils::getDisplayDimensions();
        // Navigate all the way to the left
        Desktop::switchDesktop(Desktop::DIRECTION_LEFT);

        for (int i = 0; i < desktops.size(); i++ ) {
            desktops.at(i).setupApplications(displayDimensions);
            Desktop::switchDesktop(Desktop::DIRECTION_RIGHT);
        }
    }

    void run() {
        this->desiredWorkspaceSetup = getDesktopSetupInput();
        setupApplications(this->desiredWorkspaceSetup);
    }

};

/**********************************
************** Main  **************
**********************************/

int main() {
    // const string command = "osascript -e 'tell application \"System Events\" to tell spaces preferences of expose preferences'";
    // const string command = "osascript -e 'tell application \"Finder\" to open the startup disk'";
    // const string command = "find / -type d -name \"Applications\" -maxdepth 1 -exec ls {} \\;";
    // tell application "Finder" to set the position of the front Finder window to {300, 134}
    // const string username = Utils::getStdoutFromCommand("whoami");
    // std::cout << username << std::endl;
    // Utils::getStdoutFromCommand("osascript -e 'tell application \"System Events\" to key code 124 using control down'");
    // SmartOpen * program = new SmartOpen();
    SmartOpen program;
    program.run();
    // const vector<string> APPLICATION_NAMES = getApplicationNamesList();
    // const string desiredSetup = getDesktopSetupInput();
    // setupApplications(desiredSetup);
    return 0;
}