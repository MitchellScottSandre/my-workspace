#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H
#include <string>
#include <vector>
#include <map>
#include <memory>

class FileService {
public:
    // File Names
    static const std::string ALIASES_FILE_NAME;
    static const std::string WORKSPACES_FILE_NAME;
    static const std::string OPEN_PHRASES_FILE_NAME;
    static const std::string PROCESS_NAMES_FILE_NAME;

    // Tokens
    static const std::string ALIAS_TOKEN;
    static const std::string WORKSPACE_TOKEN;
    static const std::string OPEN_PHRASES_TOKEN;
    static const std::string PROCES_NAMES_TOKEN;

    static const bool KEY_LOWERCASE = true;
    static const bool KEY_REGULAR = false;

    static bool fileExists(std::string fileName);
    static std::pair<std::string, std::string> parseKeyAndValue(std::string token, bool lowercaseKey);
    static std::map<std::string, std::string> createMapOfTokens(std::string token, std::string fileName, bool lowercaseKey);
    static std::vector<std::string> readTokenLines(std::string token, std::string fileName);

    FileService();
    ~FileService();
    static std::map<std::string, std::string> readAliases();
    static std::vector<std::string> readWorkspaces();
    static std::map<std::string, std::string> readOpenPhrases();
    static std::map<std::string, std::string>  readProcessNames();
    static void createWorkspace(std::string workspace);
};

#endif