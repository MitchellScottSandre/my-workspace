#ifndef EVENT_H
#define EVENT_H

struct Event {
    enum EventType { NULL_EVENT, DISPLAY_WELCOME, GET_DESKTOP_SETUP_INPUT };
    EventType eventType;

    Event(EventType eventType) : eventType{eventType} {}
};

#endif