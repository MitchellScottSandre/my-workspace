#include <iostream>
#include <fstream>
#include "FileService.h"
#include "Alias.h"
using namespace std;

const string FileService::ALIASES_FILE_NAME = "preferences/aliases.txt";
const string FileService::WORKSPACES_FILE_NAME = "preferences/workspaces.txt";
const string FileService::OPEN_PHRASES_FILE_NAME = "preferences/openPhrases.txt";
const string FileService::ALIAS_TOKEN = "ALIAS"; 
const string FileService::WORKSPACE_TOKEN = "WORKSPACE"; 
const string FileService::OPEN_PHRASES_TOKEN = "OPEN_PHRASE"; 

FileService::FileService() {}
FileService::~FileService() {}

/***************************************
 *            Public Methods           *
 ***************************************/

vector<shared_ptr<Alias>> FileService::readAliases() {
    vector<string> aliasTokens = FileService::readTokenLines(FileService::ALIAS_TOKEN, FileService::ALIASES_FILE_NAME);
    vector<shared_ptr<Alias>> aliases;
    for (string aliasToken : aliasTokens) {
        aliases.emplace_back(make_shared<Alias>(aliasToken));
    }

    return aliases;
 }

vector<string> FileService::readWorkspaces() {
    return FileService::readTokenLines(FileService::WORKSPACE_TOKEN, FileService::WORKSPACES_FILE_NAME);
}

vector<string> FileService::readOpenPhrases() {
    return FileService::readTokenLines(FileService::OPEN_PHRASES_TOKEN, FileService::OPEN_PHRASES_FILE_NAME);
}

void FileService::createWorkspace(string workspace) {
    fstream file;
    file.open(FileService::WORKSPACES_FILE_NAME, std::ios::app);
    file << "\n" << FileService::WORKSPACE_TOKEN << "[" << workspace << "]";
}

/***************************************
 *            Private Methods          *
 ***************************************/

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