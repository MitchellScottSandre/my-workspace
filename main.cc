#include <iostream>
#include <vector>
#include <sstream>      // std::stringstream
#include <istream>      // std::getLine
#include <string>
#include "Desktop.cc"
using namespace std;

struct foo {};

vector<string> getApplicationNamesList() {
    const string GET_APPLICATION_NAMES_COMMAND = "find / -type d -name \"Applications\" -maxdepth 1 -exec ls {} \\;";
    const string applicationNamesText = Utils::getStdoutFromCommand(GET_APPLICATION_NAMES_COMMAND);
    stringstream ss(applicationNamesText);
    vector<string> namesList;
    string tempName;

    while (getline(ss, tempName, '\n')) {
        namesList.emplace_back(tempName);
    }

    return namesList;
}

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

DisplayDimensions getDisplayDimensions() {
    const string GET_DIMENSIONS_COMMAND = "osascript -e 'tell application \"Finder\"\n get bounds of window of desktop\nend tell'";
    string dimensionsText = Utils::getStdoutFromCommand(GET_DIMENSIONS_COMMAND);
    vector<string> dimensionValues = Utils::splitByCharDelimiter(dimensionsText, ',');

    int width = stoi(dimensionValues.at(2));
    int height = stoi(dimensionValues.at(3));

    return DisplayDimensions(width, height);
}

void setupApplications(const string desiredSetup) {
    vector<Desktop> desktops = Desktop::getDesktopsFromInput(desiredSetup);
    DisplayDimensions displayDimensions = getDisplayDimensions();
    // Navigate all the way to the left
    Desktop::switchDesktop(Desktop::DIRECTION_LEFT);

    for (int i = 0; i < desktops.size(); i++ ) {
        desktops.at(i).setupApplications(displayDimensions);
        Desktop::switchDesktop(Desktop::DIRECTION_RIGHT);
    }
}

/**********************************
************** Main  **************
**********************************/

// TODO: error handling
int main() {
    // const string command = "osascript -e 'tell application \"System Events\" to tell spaces preferences of expose preferences'";
    // const string command = "osascript -e 'tell application \"Finder\" to open the startup disk'";
    // const string command = "find / -type d -name \"Applications\" -maxdepth 1 -exec ls {} \\;";
    // tell application "Finder" to set the position of the front Finder window to {300, 134}
    // const string username = Utils::getStdoutFromCommand("whoami");
    // std::cout << username << std::endl;
    // Utils::getStdoutFromCommand("osascript -e 'tell application \"System Events\" to key code 124 using control down'");

    const vector<string> APPLICATION_NAMES = getApplicationNamesList();
    const string desiredSetup = getDesktopSetupInput();
    setupApplications(desiredSetup);
    return 0;
}