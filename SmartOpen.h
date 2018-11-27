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
    ~SmartOpen();

    // Ensures: Emits events to display welcome message and get menu input
    void run();

    // Ensures: Notifies observers that the Event e has been emitted
    void emitEvent(Event e);

    // Ensures: Creates an Error event with the EventError e and emits it
    void emitError(Event::EventError e, std::string errorMessage = "");

    // Ensures: Sets up each Desktop in the workspace, moving right one desktop each time
    void setupWorkspace();

    // Ensures: If the current workspace is not already saved, saves it to preferences/workspaces.txt
    void saveWorkspace();

    // Accessors and Mutators
    void setDesktops(std::vector<std::shared_ptr<Desktop>> desktops);

    Event getLastEvent();

    std::vector<std::string> getApplicationNames();

    std::vector<std::string> getExistingWorkspaces();

    std::map<std::string, std::string> getAlternateOpenPhrases();

    std::map<std::string, std::string> getAliases();

    std::map<std::string, std::string> getProcessNames();
    
    DisplayDimensions getDisplayDimensions();
};

#endif