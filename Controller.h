#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <string>
#include <iostream>

class SmartOpen;

class Controller {
    struct ControllerImpl;
    std::unique_ptr<ControllerImpl> controllerPimpl;

    bool validDesktopSetupInputDelimiters(std::string input);
    bool validDesktopSetupInputNames(std::string input);
public:
    Controller(std::shared_ptr<SmartOpen> m);
    ~Controller();

    void receivedDesktopSetupInput(std::string input);
};

#endif