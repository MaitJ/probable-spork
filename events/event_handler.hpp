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
    static void dummy() {};
};

struct SubscriberBase {
    SubscriberBase() {}
    virtual ~SubscriberBase();

    virtual void callback();

};

struct Subscriber : public SubscriberBase {
    std::function<void()> callback_fn;
    void callback() override;
    Subscriber(std::function<void()> callback_fn) : callback_fn {callback_fn} {}
};

template <typename T>
struct SubscriberArgs : public SubscriberBase {
    std::function<void(T)> callback_fn;

    void callback() override;

public:
    SubscriberArgs(std::function<void(T)> callback_fn) : callback_fn {callback_fn} {}
};

class EventHandler {

public:

    static std::map<unique_id_type, std::queue<Event*>> event_args_queue;
    static std::map<unique_id_type, std::vector<SubscriberBase*>> subscribers_args;


    static std::queue<Event> event_queue;
    static std::map<int, std::vector<Subscriber>> subscribers;

    static void pollEvents();

    static void registerSubscriber(Event event, std::function<void()> callback);

    template <typename T>
    static void registerSubscriber(EventArgs<T> event, std::function<void(T)> callback) {
        SubscriberArgs<T>* new_subscriber = new SubscriberArgs<T>(callback);
        EventHandler::subscribers_args[EventId<T>::get_unique_id()].push_back(new_subscriber);
    }

    static void emitEvent(Event event);
    template <typename T>
    static void emitEvent(EventArgs<T> event) {
        EventArgs<T>* event_ptr = new EventArgs<T>(event.event_type, event.val);
        EventHandler::event_args_queue[EventId<T>::get_unique_id()].push(event_ptr);
    };
};


template <typename T>
void SubscriberArgs<T>::callback() {
    Event* cur_event = EventHandler::event_args_queue[EventId<T>::get_unique_id()].front();
    EventArgs<T>* cur_event_cast = static_cast<EventArgs<T>*>(cur_event);
    this->callback_fn(cur_event_cast->val);
};

#endif
