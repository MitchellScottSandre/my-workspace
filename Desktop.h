#ifndef DESKTOP_H
#define DESKTOP_H

#include <string>
#include <memory>
#include <vector>

class Application;
class DisplayDimensions;

class Desktop {
private:
    struct DesktopImpl;
    std::unique_ptr<DesktopImpl> desktopPimpl;
public:
    enum SWITCH_DESKTOP_DIRECTION { LEFT, RIGHT };

    Desktop(std::shared_ptr<Application> leftApp, std::shared_ptr<Application> rightApp, DisplayDimensions displayDimensions);
    Desktop(std::shared_ptr<Application> centreApp, DisplayDimensions displayDimensions);
    ~Desktop();

    void setupDesktop();
    // static std::vector<Desktop> getDesktopsFromInput(std::string input);
};

#endif