#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "events.hpp"
#include <functional>

struct SubscriberBase {
    EventType event_type;

    SubscriberBase(EventType event_type);
    virtual ~SubscriberBase() = default;

    virtual void callback(event_id_type event_id) {}

};

template <typename T>
struct Subscriber : public SubscriberBase {
    std::function<void(T)> callback_fn;
    void callback(event_id_type event_id) override;
    virtual ~Subscriber() = default;

public:
    Subscriber(std::function<void(T)> callback_fn, EventType event_type) : callback_fn {callback_fn}, SubscriberBase(event_type) {}
};

template<>
struct Subscriber<void> : public SubscriberBase {
    std::function<void()> callback_fn;
    void callback(event_id_type event_id) override;
    virtual ~Subscriber() = default;

public:
    Subscriber(std::function<void()> callback_fn, EventType event_type) : SubscriberBase(event_type),callback_fn {callback_fn} {}
};


#endif
