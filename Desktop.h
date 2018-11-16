#ifndef DESKTOP_H
#define DESKTOP_H

#include <string>
#include <memory>
#include <vector>

class Application;
// class DisplayDimensions;

class Desktop {
private:
    struct DesktopImpl;
    std::unique_ptr<DesktopImpl> desktopPimpl;
public:
    enum SWITCH_DESKTOP_DIRECTION { LEFT, RIGHT };

    Desktop(std::shared_ptr<Application> leftApp, std::shared_ptr<Application> rightApp);
    Desktop(std::shared_ptr<Application> centreApp);
    ~Desktop();

    void setupDesktop();
    // static bool parseDesktopTokensFromInput(std::vector<std::string> desktopTokens, std::string input);
    // static std::vector<Desktop> getDesktopsFromInput(std::string input);
};

#endif