#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <vector>
#include <queue>
#include <functional>
#include "events.hpp"
#include "subscriber.hpp"
#include <typeinfo>
#include <map>
#include <iostream>
#include <fmt/core.h>
#include <glm/glm.hpp>


class EventHandler {

public:

    static std::map<event_id_type, std::queue<EventBase*>> event_args_queue;
    static std::map<event_id_type, std::vector<SubscriberBase*>> subscribers_args;

    static void pollEvents();

    template <typename T, EventType event_type, class AssociatedClass>
    static void registerSubscriber(AssociatedClass* obj_ptr, void (AssociatedClass::*callback_fn_ptr)(T)) {
        std::function<void(T)> callback_fn = std::bind(callback_fn_ptr, obj_ptr, std::placeholders::_1);
        Subscriber<T, AssociatedClass>* new_subscriber = new Subscriber<T, AssociatedClass>(callback_fn, event_type, obj_ptr);
        event_id_type event_id = EventId::get_unique_id<T>(event_type);
        EventHandler::subscribers_args[event_id].push_back(new_subscriber);
    }

    template <EventType event_type, class AssociatedClass>
    static void registerSubscriber(AssociatedClass* obj_ptr, void (AssociatedClass::*callback_fn_ptr)()) {
        std::function<void()> callback_fn = std::bind(callback_fn_ptr, obj_ptr);
        Subscriber<void, AssociatedClass>* new_subscriber = new Subscriber<void, AssociatedClass>(callback_fn, event_type, obj_ptr);
        event_id_type event_id = EventId::get_unique_id<void>(event_type);
        EventHandler::subscribers_args[event_id].push_back(new_subscriber);
    }



    template <typename T, EventType event_type, class AssociatedClass>
    static void unsubscribe(AssociatedClass* obj, void (AssociatedClass::*fn)(T)) {
        event_id_type event_id = EventId::get_unique_id<T>(event_type);

        int i = 0;
        for (SubscriberBase* subscriber : EventHandler::subscribers_args[event_id]) {
            Subscriber<T, AssociatedClass>* cast = static_cast<Subscriber<T, AssociatedClass>*>(subscriber);
            
            if(cast->obj_ptr) 
                if (cast->obj_ptr == obj)
                    EventHandler::subscribers_args[event_id].erase(EventHandler::subscribers_args[event_id].begin() + i);

            ++i;
        }
    }

    template <EventType event_type, class AssociatedClass>
    static void unsubscribe(AssociatedClass* obj, void (AssociatedClass::*fn)()) {
        event_id_type event_id = EventId::get_unique_id<void>(event_type);

        int i = 0;
        for (auto& subscriber : EventHandler::subscribers_args[event_id]) {
            Subscriber<void, AssociatedClass>* cast = static_cast<Subscriber<void, AssociatedClass>*>(subscriber);

            if (cast->obj_ptr)
                if (cast->obj_ptr == obj)
                    EventHandler::subscribers_args[event_id].erase(EventHandler::subscribers_args[event_id].begin() + i);

            ++i;

        }
    }


    static void emitEvent(Event<void> event);

    template <typename T>
    static void emitEvent(Event<T> event) {
        Event<T>* event_ptr = new Event<T>(event.event_type, event.val);
        event_id_type event_id = EventId::get_unique_id<T>(event.event_type);
        EventHandler::event_args_queue[event_id].push(event_ptr);
    };
};

template <typename T, class AssociatedClass>
void Subscriber<T, AssociatedClass>::callback(event_id_type event_id) {
    EventBase* cur_event = EventHandler::event_args_queue[event_id].front();
    Event<T>* cur_event_cast = static_cast<Event<T>*>(cur_event);
    this->callback_fn(cur_event_cast->val);
};



#endif
