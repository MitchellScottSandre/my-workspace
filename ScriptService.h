#ifndef SCRIPT_SERVICE_H
#define SCRIPT_SERVICE_H
#include <string>
#include <set>

class ScriptService {
private:
    // std::string formatAppName(std::string name);
public:
    static std::string executeCommand(std::string cmd);

    static std::set<std::string> getApplicationNames();
};
#endif