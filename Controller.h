#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <string>
#include <iostream>

class SmartOpen;

class Controller {
    struct ControllerImpl;
    std::unique_ptr<ControllerImpl> controllerPimpl;
    static const bool VALID = true;
    static const bool ERROR = false;
    bool validDesktopSetupInput(const std::string input);
    bool parseApplicationTokens(std::vector<std::shared_ptr<Application>> & applications, std::string desktopToken);
    bool parseDesktopTokens(std::vector<std::shared_ptr<Desktop>> & desktops, const std::string input);
public:
    Controller(std::shared_ptr<SmartOpen> m);
    ~Controller();

    void receivedDesktopSetupInput(std::string input);
};

#endif