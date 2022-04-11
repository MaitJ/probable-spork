#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <vector>
#include <queue>
#include <functional>
#include "events.hpp"
#include <typeinfo>
#include <map>

typedef void (*unique_id_type)();
template <typename... Arguments>
struct EventId {
    static constexpr inline unique_id_type get_unique_id() {
        return &EventId::dummy;
    }

private:
    static void dummy();
};

struct SubscriberBase {
    virtual void callback();

public:
    SubscriberBase() {}
};

struct Subscriber : SubscriberBase {
    std::function<void()> callback_fn;
    void callback() override;
    Subscriber(std::function<void()> callback_fn) : callback_fn {callback_fn} {}
};

template <typename T>
struct SubscriberArgs : SubscriberBase {
    std::function<void(T)> callback_fn;
    void callback() override;

public:
    SubscriberArgs(std::function<void(T)> callback_fn) : callback_fn {callback_fn} {}
};

class EventHandler {

public:

    static std::map<int, std::vector<Event>> event_args_queue;
    static std::map<int, std::vector<SubscriberBase>> subscribers_args;


    static std::queue<Event> event_queue;
    static std::map<int, std::vector<Subscriber>> subscribers;

    static void pollEvents();

    static void registerSubscriber(Event event, std::function<void()> callback);
    template <typename T>
    static void registerSubscriber(EventArgs<T> event, std::function<void(T)> callback);

    static void emitEvent(Event event);
    template <typename T>
    static void emitEvent(EventArgs<T> event);
};

#endif
