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
    void openWithAlternatePhrase();
    void putInPosition();
    void bringToFront();
    void setFullScreen();
public:
    enum ApplicationPosition { LEFT, MIDDLE, RIGHT, FULL_SCREEN };
    static const int LEFT_INDEX = 0;
    static const int RIGHT_INDEX = 1;

    Application(std::string appName, std::string alternateOpenPhrase, std::string processName, ApplicationPosition position, DisplayDimensions displayDimensions);

    ~Application();

    // Ensures: Opens the application (launching, new window, or new document, etc) and puts it into the correct position on the screen
    void setupApplication();

    // Returns: The application name, surrounded by Full Screen Window delimiters, if the app was set to be in full screen
    std::string toString();
};

#endif