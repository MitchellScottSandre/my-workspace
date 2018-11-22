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
    bool validDesktopSetupInput(const std::string input);
    bool parseDesktopTokens(std::vector<std::shared_ptr<Desktop>> & desktops, const std::string input);
    bool parseApplicationTokens(std::vector<std::shared_ptr<Application>> & applications, std::string desktopToken);
    bool validFullScreenDelimiter(std::string & applicationToken, bool & appIsFullScreen, const int tokenIndex);
    bool validNumberInput(std::string input, int min, int max);
    std::string getSystemApplicationName(std::string applicationToken);
    std::shared_ptr<Application> createApplication(std::string systemAppName, bool fullScreen, int numTokensInDesktop, int tokenIndex);
    std::string getAlternateApplicationOpenPhrase(std::string systemAppName);
public:
    Controller(std::shared_ptr<SmartOpen> m);
    ~Controller();

    void receivedMenuInput(std::string input);
    void parseWorkspaceInput(std::string input, bool isExistingWorkspace); //TODO: create static const bool for this
    void receivedSaveWorkspaceMenuInput(std::string input);
    void receivedLoadExistingWorkspaceInput(std::string input);
};

#endif