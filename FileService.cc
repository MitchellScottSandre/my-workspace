#include <iostream>
#include <fstream>
#include "FileService.h"
#include "Alias.h"
using namespace std;

const string FileService::SETTINGS_FILE_NAME = "settings.txt";
const string FileService::ALIAS_TOKEN = "ALIAS"; 
const string FileService::WORKSPACE_TOKEN = "WORKSPACE"; 

FileService::FileService() {}
FileService::~FileService() {}

/***************************************
 *            Public Methods           *
 ***************************************/

vector<shared_ptr<Alias>> FileService::readAliases() {
    vector<string> aliasTokens = FileService::readTokenLines(FileService::ALIAS_TOKEN);
    vector<shared_ptr<Alias>> aliases;
    for (string aliasToken : aliasTokens) {
        aliases.emplace_back(make_shared<Alias>(aliasToken));
    }

    return aliases;
 }

vector<string> FileService::readWorkspaces() {
    return FileService::readTokenLines(FileService::WORKSPACE_TOKEN);
}

/***************************************
 *            Private Methods          *
 ***************************************/

vector<string> FileService::readTokenLines(string token) {
    vector<string> tokens;
    if (!FileService::settingsFileExists()) {
        return tokens;
    }

    ifstream file(FileService::SETTINGS_FILE_NAME);
    string line;
    bool readingTokens = false;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.substr(0, token.length()) == token) {
                readingTokens = true;
                int contentLength = line.length() - token.length() - 2;
                tokens.emplace_back(line.substr(token.length() + 1, contentLength));
            } else if (readingTokens == true) {
                file.close();
                break;
            }
        }
    }

    return tokens;
}

bool FileService::settingsFileExists() {
    ifstream inputStream(FileService::SETTINGS_FILE_NAME.c_str());
    return inputStream.good();
}