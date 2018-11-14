#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>

class SmartOpen;

class Controller {
    struct ControllerImpl;
    std::unique_ptr<ControllerImpl> controllerPimpl;

public:
    Controller(std::shared_ptr<SmartOpen> m);
    ~Controller();
};

#endif