#ifndef SCRIPT_SERVICE_H
#define SCRIPT_SERVICE_H
#include <string>
#include <vector>

class DisplayDimensions;

class ScriptService {
private:
    // Returns: removes ".app" from the application name
    static std::string formatAppName(std::string appName);
public:
    enum DesktopDirection { LEFT, RIGHT };

    // Ensures: Executes the cmd command
    // Returns: Terminal output of the cmd command
    static std::string executeCommand(std::string cmd);

    // Ensures: Delays terminal execution by duration in seconds
    static void delay(int duration);

    // Requires: The current desktop not to be the first (if going left) or last (if going right) desktop
    // Ensures: Switches desktops (moving either left or right)
    static void switchDesktops(DesktopDirection direction);

    // Returns: If an application is running (i.e. if it's process is active)
    static bool isApplicationRunning(std::string appName);

    // Returns: A vector of all of the application names takes from USER_HOME/Applications/**
    static std::vector<std::string> getApplicationNames();

    // Returns: A DisplayDimensions object for the current screen on which the application is run
    static DisplayDimensions getDisplayDimensions();
};

#endif