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

template <typename T, class AssociatedClass>
struct Subscriber : public SubscriberBase {
    std::function<void(T)> callback_fn;
    AssociatedClass* obj_ptr; 
    void callback(event_id_type event_id) override;
    virtual ~Subscriber() = default;

public:
    Subscriber(std::function<void(T)> callback_fn, EventType event_type, AssociatedClass* obj_ptr) : callback_fn {callback_fn}, SubscriberBase(event_type), obj_ptr{obj_ptr} {}
};

template<class AssociatedClass>
struct Subscriber<void, AssociatedClass> : public SubscriberBase {
    std::function<void()> callback_fn;
    AssociatedClass* obj_ptr;
    void callback(event_id_type event_id) override {
        this->callback_fn();
    }
    virtual ~Subscriber() = default;

public:
    Subscriber(std::function<void()> callback_fn, EventType event_type, AssociatedClass* obj_ptr) : SubscriberBase(event_type),callback_fn {callback_fn}, obj_ptr{obj_ptr} {}
};


#endif
