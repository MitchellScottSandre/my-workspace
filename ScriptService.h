#ifndef SCRIPT_SERVICE_H
#define SCRIPT_SERVICE_H
#include <string>
#include <vector>

class DisplayDimensions;

class ScriptService {
private:
    static std::string formatAppName(std::string appName);
public:
    enum DesktopDirection { LEFT, RIGHT };

    // Ensures: Executes the cmd command
    // Returns: Terminal output of the cmd command
    static std::string executeCommand(std::string cmd);

    // Ensures: Delays terminal execution by duration in seconds
    static void delay(int duration);

    // Ensures: 
    static void switchDesktops(DesktopDirection direction);
    static bool isApplicationRunning(std::string appName);
    static std::vector<std::string> getApplicationNames();
    static DisplayDimensions getDisplayDimensions();
};
#endif