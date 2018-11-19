#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H
#include <string>
#include <vector>

class FileService {
private:
    // static const int NUMBER_WORKSPACES;
    static const std::string SETTINGS_FILE_NAME;
public:

    FileService();
    ~FileService();
    static void createWorkspace(std::string workspace);
    static std::string readWorkspace(int index);
    static std::vector<std::string> readAllWorkspaces();
};

#endif