#ifndef SCRIPT_SERVICE_H
#define SCRIPT_SERVICE_H
#include <string>
#include <set>

class ScriptService {
private:
    static std::string formatAppName(std::string appName);
public:
    static std::string executeCommand(std::string cmd);
    static std::set<std::string> getApplicationNames();
    static void delay(int duration);
};
#endif