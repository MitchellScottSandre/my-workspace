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
    
public:
    View(std::shared_ptr<Controller> c, std::shared_ptr<SmartOpen> m);
    ~View();

    void getNotified();
    void displayWelcome();

};


#endif