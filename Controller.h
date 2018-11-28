#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <string>
#include <iostream>

class SmartOpen;
class Desktop;
class Application;

class Controller {
    struct ControllerImpl;
    std::unique_ptr<ControllerImpl> controllerPimpl;

    
    static const bool VALID = true;
    static const bool ERROR = false;
    static const std::string NULL_APP_NAME;

    // Returns: True if the provided desktop setup input is valid (all applications exist, correctr syntax), otherwise false
    bool validDesktopSetupInput(const std::string input);

    // Returns: True if the applicationToken begins with < and ends with >
    // Modifies: if is a full screen token, removes the full screen delimiters from the applicationToken, and sets appIsFullScreen to true
    bool validFullScreenDelimiter(std::string & applicationToken, bool & appIsFullScreen, const int tokenIndex);

    // Returns: True if the input string can be parsed to an integer and is within the [min, max] range
    bool validNumberInput(std::string input, int min, int max);

    // Returns: True if the desktop tokens can correctly be parsed
    // Modifies: the vector of desktop shared pointers, adding Desktops with valid Applications
    bool parseDesktopTokens(std::vector<std::shared_ptr<Desktop>> & desktops, const std::string input);

    // Returns: True if the Application tokens can correctly be parsed
    // Modifies: the vector of Application shared pointers, adding Desktops with valid Applications
    bool parseApplicationTokens(std::vector<std::shared_ptr<Application>> & applications, std::string desktopToken);

    // Returns: A share pointer to an Application
    std::shared_ptr<Application> createApplication(std::string systemAppName, bool fullScreen, int numTokensInDesktop, int tokenIndex);

    // Returns: The correct system application name, as the name given in the USER_HOME/Applications folder, handling cases where
    //          incorrect casing is used, as well as when an Alias is used (ie. "Chrome" for "Google Chrome")
    std::string getSystemApplicationName(std::string applicationToken);

    // Returns: The alternate application open phrase used to open the application if another window is already acitve, or "" if
    //          no such phrase exists in preferences/openPhrases.txt
    std::string getAlternateApplicationOpenPhrase(std::string systemAppName);

    // Returns: The process name of the application taken from preferences/processNames.txt, or "" if no such matching name exists
    std::string getProcessName(std::string systemAppName);
public:
    Controller(std::shared_ptr<SmartOpen> m);

    ~Controller();

    // Input Handling Functions
    void receivedMenuInput(std::string input);
    void parseWorkspaceInput(std::string input, bool isExistingWorkspace); 
    void receivedSaveWorkspaceMenuInput(std::string input);
    void receivedLoadExistingWorkspaceInput(std::string input);
};

#endif