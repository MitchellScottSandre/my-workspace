#ifndef SMART_OPEN_H
#define SMART_OPEN_H
#include <string>
#include <vector>
#include <memory>
#include <vector>
#include <map>
#include "Subject.h"
#include "Event.h"

class Desktop;
class DisplayDimensions;

class SmartOpen: public Subject {
private:
    struct SmartOpenImpl;
    std::unique_ptr<SmartOpenImpl> smartOpenPimpl;

    bool workspaceAlreadyExists(std::string workspace);
public:
    SmartOpen();
    virtual ~SmartOpen();

    Event getLastEvent();
    void run();
    void emitError(Event::EventError e, std::string errorMessage = "");
    void emitEvent(Event e);
    void setupWorkspace();
    void setDesktops(std::vector<std::shared_ptr<Desktop>> desktops);
    void saveWorkspace();

    std::vector<std::string> getApplicationNames();
    std::vector<std::string> getExistingWorkspaces();
    std::map<std::string, std::string> getAlternateOpenPhrases();
    std::map<std::string, std::string> getAliases();
    std::map<std::string, std::string> getProcessNames();
    DisplayDimensions getDisplayDimensions();
};

#endif