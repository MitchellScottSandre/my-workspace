#include <iostream>
#include <sstream>      // std::stringstream
#include <istream>      // std::getLine
#include <stdio.h>
#include <stdlib.h> // TODO: remove unused ones
#include "ScriptService.h"
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
    // TODO: find all files in Applications (and in folders inside of applications)
    // const string GET_APPLICATION_NAMES_COMMAND = "find / -type d -name \"Applications\" -exec find . -type f -name '*.app' -printf '%TY-%Tm-%Td %TT %p\n' {} \\;";
    const string GET_APPLICATION_NAMES_COMMAND = "find / -type d -name \"Applications\" -maxdepth 1 -exec ls {} \\;";
    const string applicationNamesText = executeCommand(GET_APPLICATION_NAMES_COMMAND);
    stringstream ss(applicationNamesText);
    set<string> namesSet;
    string tempName;

    while (getline(ss, tempName, '\n')) {
        namesSet.insert(tempName);
        cout << "--> " << tempName << endl;
        //TODO: remove the .app
    }

    return namesSet;
}

// string ScriptService::fot