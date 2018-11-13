#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>      // std::stringstream
#include <istream>      // std::getLine
#include <string>
using namespace std;

class Desktop {
    public:
        string app1;
        string app2;

        Desktop(string left, string right) : app1{left}, app2{right} {}
};

/**********************************
******** Helper Functions *********
**********************************/

string trim(string x) {
    // Trim start of word
    char c = x.at(0);
    while (c == ' ') {
        x.erase(0, 1);
        c = x.at(0);
    }

    // Trim end of word
    c = x.at(x.length() - 1);
    while (c == ' ') {
        x.erase(x.length() - 1, 1);
        c = x.at(x.length() - 1);
    
    }
    return x;
}

// Not my original creation.
// taken from https://www.jeremymorgan.com/tutorials/c-programming/how-to-capture-the-output-of-a-linux-command-in-c/
string getStdoutFromCommand(string cmd) {
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, max_buffer, stream) != NULL) {
                data.append(buffer);
            }
        }
        pclose(stream);
    }
    return data;
}

vector<string> getApplicationNamesList() {
    const string GET_APPLICATION_NAMES_COMMAND = "find / -type d -name \"Applications\" -maxdepth 1 -exec ls {} \\;";
    const string applicationNamesText = getStdoutFromCommand(GET_APPLICATION_NAMES_COMMAND);
    stringstream ss(applicationNamesText);
    vector<string> namesList;
    string tempName;

    while (getline(ss, tempName, '\n')) {
        namesList.emplace_back(tempName);
        // cout << tempName << endl;
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

vector<Desktop *> getDesktopsFromInput(string input) {
    vector<Desktop *> desktops;

    const string desktopDelimiter = "||";
    const string applicationDelimiter = "|";
    size_t desktopDelimeterIndex = 0;
    string desktopToken;

    while ((desktopDelimeterIndex = input.find(desktopDelimiter)) != string::npos) {
        // Parse desktop token
        desktopToken = input.substr(0, desktopDelimeterIndex);
        int applicationDelimeterIndex = desktopToken.find(applicationDelimiter);
        string leftApp = trim(desktopToken.substr(0, applicationDelimeterIndex));
        string rightApp = trim(desktopToken.substr(applicationDelimeterIndex + 1));

        // Create Desktop
        desktops.emplace_back(new Desktop(leftApp, rightApp));

        // Remove token from input 
        input.erase(0, desktopDelimeterIndex + desktopDelimiter.length());
    }

    return desktops;
}

void switchDesktop(string direction) {
    string directionKeyCode;
    if (direction == "left") {
        directionKeyCode = "123";
    } else {
        directionKeyCode = "124";
    }

    string command = "osascript -e 'tell application \"System Events\" to key code " + directionKeyCode + " using control down'";
    getStdoutFromCommand(command);
}

void addApplications() {
    // Navigate all the way to the left
    switchDesktop("left");
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
    // const string username = getStdoutFromCommand("whoami");
    // std::cout << username << std::endl;

    const vector<string> APPLICATION_NAMES = getApplicationNamesList();
    const string desiredSetup = getDesktopSetupInput();
    const vector<Desktop *> desktops = getDesktopsFromInput(desiredSetup);
    addApplications();
    return 0;
}