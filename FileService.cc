#include <iostream>
#include <fstream>
#include "FileService.h"
#include "StringUtils.h"
using namespace std;

const string FileService::ALIASES_FILE_NAME = "preferences/aliases.txt";
const string FileService::WORKSPACES_FILE_NAME = "preferences/workspaces.txt";
const string FileService::OPEN_PHRASES_FILE_NAME = "preferences/openPhrases.txt";
const string FileService::ALIAS_TOKEN = "ALIAS"; 
const string FileService::WORKSPACE_TOKEN = "WORKSPACE"; 
const string FileService::OPEN_PHRASES_TOKEN = "OPEN_PHRASE"; 

FileService::FileService() {}
FileService::~FileService() {}

map<string, string> FileService::readAliases() {
    return FileService::createMapOfTokens(FileService::ALIAS_TOKEN, FileService::ALIASES_FILE_NAME, true);
}

vector<string> FileService::readWorkspaces() {
    return FileService::readTokenLines(FileService::WORKSPACE_TOKEN, FileService::WORKSPACES_FILE_NAME);
}

map<string, string> FileService::readOpenPhrases() {
    return FileService::createMapOfTokens(FileService::OPEN_PHRASES_TOKEN, FileService::OPEN_PHRASES_FILE_NAME, false);
}

void FileService::createWorkspace(string workspace) {
    fstream file;
    file.open(FileService::WORKSPACES_FILE_NAME, std::ios::app);
    file << "\n" << FileService::WORKSPACE_TOKEN << "[" << workspace << "]";
}

map<string, string> FileService::createMapOfTokens(string token, string fileName, bool lowercaseKey) {
    map<string, string> map;
    vector<string> tokens = FileService::readTokenLines(token, fileName);

    for (string token : tokens) {
        cout << "token is: " << token << endl;
        pair<string, string> kvp = FileService::parseKeyAndValue(token, lowercaseKey);
        if (kvp.first != "" && kvp.second != "") {
            cout << "KVP is (" << kvp.first << ", " << kvp.second << ")" << endl;
            map.insert(kvp);
        }
    }

    return map;
}

vector<string> FileService::readTokenLines(string token, string fileName) {
    vector<string> tokens;
    if (!FileService::fileExists(fileName)) {
        return tokens;
    }

    ifstream file(fileName);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.substr(0, token.length()) == token) {
                int contentLength = line.length() - token.length() - 2;
                tokens.emplace_back(line.substr(token.length() + 1, contentLength));
            }
        }
    }

    file.close();

    return tokens;
}

bool FileService::fileExists(string fileName) {
    ifstream inputStream(fileName.c_str());
    return inputStream.good();
}

pair<string, string> FileService::parseKeyAndValue(string token, bool lowercaseKey) {
    string key = "";
    string value = "";
    int colonIndex = token.find(":");
    if (colonIndex != string::npos) {
        key = lowercaseKey ? StringUtils::str_tolower(token.substr(1, colonIndex - 2)) : token.substr(1, colonIndex - 2);
        value = token.substr(colonIndex + 2, token.length() - colonIndex - 3);
    }

    return pair<string, string>(key, value);
}