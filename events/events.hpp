#ifndef EVENTS_H
#define EVENTS_H


enum EventType {
    MOVE_LEFT = 0,
    LIGHT_TOGGLE = 1,
    MOVE_CAM_VEC2 = 2,
    COUNT = 3
};

class EventBase {
public:
    EventType event_type;
    EventBase(EventType ev_type) : event_type{ev_type} {}
    virtual ~EventBase() = default;
};

template <typename T>
class Event : public EventBase {
public:
    Event(EventType ev_type, T value) : EventBase(ev_type), val{value} {}
    T val;
};

template <>
class Event<void> : public EventBase{

public:
    Event(EventType ev_type) : EventBase(ev_type) {}
};

#endif
