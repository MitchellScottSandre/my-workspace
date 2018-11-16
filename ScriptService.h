#ifndef SCRIPT_SERVICE_H
#define SCRIPT_SERVICE_H
#include <string>
#include <set>

class DisplayDimensions;

class ScriptService {
private:
    static std::string formatAppName(std::string appName);
public:
    enum DesktopDirection { LEFT, RIGHT };
    static std::string executeCommand(std::string cmd);
    static std::set<std::string> getApplicationNames();
    static void delay(int duration);
    static void switchDesktops(DesktopDirection direction);
    static DisplayDimensions getDisplayDimensions();
};
#endif