#include <iostream>
#include <sstream>      
#include <istream>    
#include "ScriptService.h"
#include "StringUtils.h"
#include "DisplayDimensions.h"
using namespace std;

bool ScriptService::isApplicationRunning(string appName) {
    string command = "osascript -e 'application\"" + appName + "\" is running'";
    string output = ScriptService::executeCommand(command);
    cout << command << endl;
    if (output.find("true") != string::npos) return true;
    return false;
}

// This function is taken from https://www.jeremymorgan.com/tutorials/c-programming/how-to-capture-the-output-of-a-linux-command-in-c/
string ScriptService::executeCommand(string cmd) {
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

vector<string> ScriptService::getApplicationNames() {
    const string GET_APPLICATION_NAMES_COMMAND = "cd //Applications && find . -name '*.app' -maxdepth 2 -exec basename {} \\; | sort";
    const string applicationNamesText = executeCommand(GET_APPLICATION_NAMES_COMMAND);
    stringstream ss(applicationNamesText);
    vector<string> namesList;
    string appName;

    while (getline(ss, appName, '\n')) {
        namesList.emplace_back(ScriptService::formatAppName(appName));
    }

    return namesList;
}

void ScriptService::delay(int duration) {
    string command = "osascript -e 'delay " + to_string(duration) + "'";
    ScriptService::executeCommand(command);
}

string ScriptService::formatAppName(string appName) {
    const string fileExt = ".app";
    if (appName.substr(appName.length() - fileExt.length(), fileExt.length()) == fileExt) {
        return appName.substr(0, appName.length() - fileExt.length());
    }

    return appName;
}

DisplayDimensions ScriptService::getDisplayDimensions() {
    const string GET_DIMENSIONS_COMMAND = "osascript -e 'tell application \"Finder\"\n get bounds of window of desktop\nend tell'";
    string dimensionsText = ScriptService::executeCommand(GET_DIMENSIONS_COMMAND);
    vector<string> dimensionValues;
    StringUtils::split(dimensionValues, dimensionsText, ',');

    int width = stoi(dimensionValues.at(2));
    int height = stoi(dimensionValues.at(3));

    return DisplayDimensions(width, height);
}

void ScriptService::switchDesktops(DesktopDirection direction) {
    string directionKeyCode = "";
    if (direction == DesktopDirection::LEFT) {
        directionKeyCode = "123";
    } else if (direction == DesktopDirection::RIGHT) {
        directionKeyCode = "124";
    }

    string command = "osascript -e 'tell application \"System Events\" to key code " + directionKeyCode + " using control down'";
    ScriptService::executeCommand(command);
}
