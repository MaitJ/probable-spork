#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <vector>
#include <queue>
#include <functional>
#include "events.hpp"
#include "subscriber.hpp"
#include <typeinfo>
#include <map>



class EventHandler {

public:

    static std::map<event_id_type, std::queue<EventBase*>> event_args_queue;
    static std::map<event_id_type, std::vector<SubscriberBase*>> subscribers_args;

    static void pollEvents();
    static void registerSubscriber(EventBase event, std::function<void()> callback);

    template <typename T, EventType event_type>
    static void registerSubscriber(std::function<void(T)> callback) {

        Subscriber<T>* new_subscriber = new Subscriber<T>(callback, event_type);
        event_id_type event_id = EventId::get_unique_id<T>(event_type);
        EventHandler::subscribers_args[event_id].push_back(new_subscriber);
    }

    template <EventType event_type>
    static void registerSubscriber(std::function<void()> callback) {
        Subscriber<void>* new_subscriber = new Subscriber<void>(callback, event_type);
        event_id_type event_id = EventId::get_unique_id<void>(event_type);
        EventHandler::subscribers_args[event_id].push_back(new_subscriber);
    }


    static void emitEvent(Event<void> event);

    template <typename T>
    static void emitEvent(Event<T> event) {
        Event<T>* event_ptr = new Event<T>(event.event_type, event.val);
        event_id_type event_id = EventId::get_unique_id<T>(event.event_type);
        EventHandler::event_args_queue[event_id].push(event_ptr);
    };
};

//If i move this into subscriber.cpp then, it causes circular dependency error, or smth like that
template <typename T>
void Subscriber<T>::callback(event_id_type event_id) {
    EventBase* cur_event = EventHandler::event_args_queue[event_id].front();
    Event<T>* cur_event_cast = static_cast<Event<T>*>(cur_event);
    this->callback_fn(cur_event_cast->val);
};



#endif
