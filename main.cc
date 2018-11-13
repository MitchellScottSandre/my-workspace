#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>      // std::stringstream
#include <istream>      // std::getLine
#include <string>
using namespace std;

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
    }

    return namesList;
}

int main() {
    // const string command = "osascript -e 'tell application \"System Events\" to tell spaces preferences of expose preferences'";
    // const string command = "osascript -e 'tell application \"Finder\" to open the startup disk'";
    // const string command = "find / -type d -name \"Applications\" -maxdepth 1 -exec ls {} \\;";
    // tell application "Finder" to set the position of the front Finder window to {300, 134}
    // const string username = getStdoutFromCommand("whoami");
    // std::cout << username << std::endl;

    const vector<string> APPLICATION_NAMES = getApplicationNamesList();
    return 0;
}