#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <string>

class DisplayDimensions;

class Application {
private:
    struct ApplicationImpl;
    std::unique_ptr<ApplicationImpl> applicationPimpl;

    void open();
    void putInPosition();

public:
    enum ApplicationPosition { LEFT, MIDDLE, RIGHT, FULL_SCREEN };
    Application(std::string appName, ApplicationPosition position, DisplayDimensions displayDimensions);
    ~Application();

    void setup();
    // static string parseApplications
};

#endif