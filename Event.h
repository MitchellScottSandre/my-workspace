#ifndef EVENT_H
#define EVENT_H

struct Event {
    enum EventType { DISPLAY_WELCOME };
    EventType eventType;

    Event(EventType eventType) : eventType{eventType} {}
};

#endif