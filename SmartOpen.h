#ifndef SMART_OPEN_H
#define SMART_OPEN_H
#include <string>
#include <vector>
#include <memory>
#include <vector>
#include "Subject.h"
#include "Event.h"

class Alias;
class Desktop;
class DisplayDimensions;

class SmartOpen: public Subject {
private:
    struct SmartOpenImpl;
    std::unique_ptr<SmartOpenImpl> smartOpenPimpl;

public:
    SmartOpen();
    ~SmartOpen();

    void run();
    void emitError(Event::EventError e, std::string errorMessage = "");
    void emitEvent(Event e);
    Event getLastEvent();
    void setupWorkspace();
    void setDesktops(std::vector<std::shared_ptr<Desktop>> desktops);

    std::vector<std::string> getApplicationNames();
    std::vector<std::shared_ptr<Alias>> getAliases();
    DisplayDimensions getDisplayDimensions();
};

#endif