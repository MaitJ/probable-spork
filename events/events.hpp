#ifndef EVENTS_H
#define EVENTS_H

#include <stdlib.h>

enum EventType {
    MOVE_LEFT = 0,
    LIGHT_TOGGLE = 1,
    MOVE_CAM_VEC2 = 2,
    CAMERA_ORIENTATION = 3,
    CAMERA_MOVEMENT = 4,
    COUNT = 5
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

    template <typename... Arguments>
    constexpr static inline event_id_type get_unique_id(EventType event_type) {
        const event_id_type id = counter + event_type + 10;
        return id;
    }

private:
    static std::size_t counter;
};

#endif
