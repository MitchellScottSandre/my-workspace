#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H
#include <string>
#include <vector>
#include <memory>

class Alias;
class FileService {
private:
    static const std::string SETTINGS_FILE_NAME;
    static const std::string ALIAS_TOKEN;
    static const std::string WORKSPACE_TOKEN;

    static bool settingsFileExists();
    static std::vector<std::string> readTokenLines(std::string token);
public:

    FileService();
    ~FileService();
    static std::vector<std::shared_ptr<Alias>> readAliases();
    static void createWorkspace(std::string workspace);
    static std::vector<std::string> readWorkspaces();
};

#endif