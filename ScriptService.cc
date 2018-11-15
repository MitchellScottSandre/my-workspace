#include <iostream>
#include <sstream>      // std::stringstream
#include <istream>      // std::getLine
#include <stdio.h>
#include <stdlib.h> // TODO: remove unused ones
#include "ScriptService.h"
#include "StringUtils.h"
#include "DisplayDimensions.h"
using namespace std;

// This function taken from https://www.jeremymorgan.com/tutorials/c-programming/how-to-capture-the-output-of-a-linux-command-in-c/
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

set<string> ScriptService::getApplicationNames() {
    const string GET_APPLICATION_NAMES_COMMAND = "cd //Applications && find . -name '*.app' -maxdepth 2 -exec basename {} \\; | sort";
    const string applicationNamesText = executeCommand(GET_APPLICATION_NAMES_COMMAND);
    stringstream ss(applicationNamesText);
    set<string> namesSet;
    string appName;

    while (getline(ss, appName, '\n')) {
        namesSet.insert(ScriptService::formatAppName(appName));
    }

    return namesSet;
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
