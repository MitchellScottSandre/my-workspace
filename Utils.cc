#include <string>
#include <vector>
#include <iostream>
#include <sstream>      // std::stringstream
#include <istream>      // std::getLine
#include <stdio.h>
#include <stdlib.h>
using namespace std;

namespace Utils {
    
    static vector<string> splitByCharDelimiter(string & str, char delim) {
        vector<string> data;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delim)) {
            data.emplace_back(token);
        }

        return data;
    }

    // Removes leading and trailing white space
    static string trim(string x) {
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

    // This function taken from https://www.jeremymorgan.com/tutorials/c-programming/how-to-capture-the-output-of-a-linux-command-in-c/
    static string getStdoutFromCommand(string cmd) {
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

    static void delay(int duration) {
        string command = "osascript -e 'delay " + to_string(duration) + "'";
        getStdoutFromCommand(command);
    }

    static vector<string> getApplicationNamesList() {
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

    DisplayDimensions getDisplayDimensions() {
        const string GET_DIMENSIONS_COMMAND = "osascript -e 'tell application \"Finder\"\n get bounds of window of desktop\nend tell'";
        string dimensionsText = Utils::getStdoutFromCommand(GET_DIMENSIONS_COMMAND);
        vector<string> dimensionValues = Utils::splitByCharDelimiter(dimensionsText, ',');

        int width = stoi(dimensionValues.at(2));
        int height = stoi(dimensionValues.at(3));

        return DisplayDimensions(width, height);
    }
}
