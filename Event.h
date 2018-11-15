#ifndef EVENT_H
#define EVENT_H

#include <string>

struct Event {
    enum EventType { NULL_EVENT, DISPLAY_WELCOME, GET_DESKTOP_SETUP_INPUT, INPUT_ERROR };
    enum EventError { NULL_ERROR, BAD_APPLICATION_NAME };

    EventType type;
    EventError error;
    std::string data;

    Event(EventType type = NULL_EVENT, EventError error = NULL_ERROR, std::string data = "") : 
        type{type}, error{error}, data{data} {}
};

#endif