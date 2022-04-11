#ifndef EVENTS_H
#define EVENTS_H


enum EventType {
    MOVE_LEFT = 0,
    LIGHT_TOGGLE = 1,
    MOVE_CAM_VEC2 = 2,
    COUNT = 3
};

class Event {
public:
    EventType event_type;
    Event(EventType ev_type) : event_type{ev_type} {}
};

template <typename T>
class EventArgs : public Event {
    T val;
public:
    EventArgs(EventType ev_type, T value) : Event(ev_type), val{value} {}
};

#endif
