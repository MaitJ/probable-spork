#ifndef EVENTS_H
#define EVENTS_H

#include <stdlib.h>

enum EventType {
    TEST = 0,
    MOVE_LEFT = 1,
    LIGHT_TOGGLE = 2,
    MOVE_CAM_VEC2 = 3,
    CAMERA_ORIENTATION = 4,
    CAMERA_MOVEMENT = 5,
    COUNT = 6
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

typedef std::size_t event_id_type;

struct EventId {

    template <typename T>
    static inline event_id_type get_unique_id(EventType event_type) {
        static event_id_type id = (counter++) + event_type + 10;
        return id;
    }

private:
    static std::size_t counter;
    static std::size_t event_counter;
};

#endif
