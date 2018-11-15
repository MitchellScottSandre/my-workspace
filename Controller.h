#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <string>
#include <iostream>

class SmartOpen;

class Controller {
    struct ControllerImpl;
    std::unique_ptr<ControllerImpl> controllerPimpl;

    bool validDesktopSetupInputDelimiters(const std::string input);
    bool validDesktopSetupInputNames(const std::string input);
    // bool validApplicationName(const std::string appName);
public:
    Controller(std::shared_ptr<SmartOpen> m);
    ~Controller();

    void receivedDesktopSetupInput(std::string input);
};

#endif