#ifndef EVENTS_H
#define EVENTS_H

enum EventType {
    MOVE_LEFT = 0,
    LIGHT_TOGGLE = 1,
    COUNT = 2
};

template <typename T>
class Event {
    EventType event_type;
    T val;
};

#endif
