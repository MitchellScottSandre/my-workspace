#ifndef VIEW_H
#define VIEW_H
#include <string>
#include <memory>
#include "SmartOpen.h"
#include "Observer.h"

class Controller;

class View: public Observer {
private:
    struct ViewImpl;
    std::unique_ptr<ViewImpl> viewPimpl;

    void displayWelcome();
    void getMenuInput();
    void getDesktopSetupInput();
    void getExistingWorkspaceInput();
    void displayError(Event::EventError error, std::string errorMessage);
public:
    static const std::string DESKTOP_DELIMITER;
    static const std::string APPLICATION_DELIMITER;
    static const char FULL_SCREEN_LEFT_DELIMITER;
    static const char FULL_SCREEN_RIGHT_DELIMITER;

    View(std::shared_ptr<Controller> c, std::shared_ptr<SmartOpen> m);
    ~View();

    void getNotified();
};


#endif