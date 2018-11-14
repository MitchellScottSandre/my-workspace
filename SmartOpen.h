#ifndef SMART_OPEN_H
#define SMART_OPEN_H
#include <string>
#include <vector>
#include <memory>
#include "Subject.h"
#include "Event.h"

class SmartOpen: public Subject {
private:
    struct SmartOpenImpl;
    std::unique_ptr<SmartOpenImpl> smartOpenPimpl;

public:
    static const int POSITION_LEFT;
    static const int POSITION_MIDDLE;
    static const int POSITION_RIGHT;
    static const int FULL_SCREEN;

    SmartOpen();
    ~SmartOpen();

    void run();
    void emitEvent(Event e);
    Event getLastEvent();
};

#endif