#ifndef EVENT_H
#define EVENT_H

#include <string>

struct Event {
    enum EventType { NULL_EVENT, DISPLAY_WELCOME, GET_MENU_INPUT, GET_EXISTING_WORKSPACE_INPUT, GET_DESKTOP_SETUP_INPUT, ASK_TO_SAVE_WORKSPACE, ERROR };
    enum EventError { NULL_ERROR, BAD_MENU_INPUT, BAD_SAVE_INPUT, BAD_APPLICATION_NAME, TOO_MANY_APPLICATIONS, INVALID_FULLSCREEN };

    EventType type;
    EventError error;
    std::string data;

    Event(EventType type = NULL_EVENT, EventError error = NULL_ERROR, std::string data = "") : 
        type{type}, error{error}, data{data} {}
};

#endif