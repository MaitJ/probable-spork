#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <vector>
#include <queue>
#include <functional>
#include "events.hpp"
#include "subscriber.hpp"
#include <typeinfo>
#include <iostream>
#include <map>
#include <iostream>
#include <fmt/core.h>
#include <glm/glm.hpp>


class EventHandler {

public:

    static std::map<event_id_type, std::queue<EventBase*>> event_args_queue;
    static std::map<event_id_type, std::vector<SubscriberBase*>> subscribers_args;

    static void pollEvents();


    template <typename T, class AssociatedClass>
    static bool subscriberExists(Subscriber<T, AssociatedClass>* new_subscriber, event_id_type event_id){
        bool exists = false;
        for (auto& subscriber : EventHandler::subscribers_args[event_id]) {
            Subscriber<void, AssociatedClass>* cast = static_cast<Subscriber<void, AssociatedClass>*>(subscriber);

            if (cast->obj_ptr)
                if(cast->obj_ptr == new_subscriber->obj_ptr)
                    exists = true;
        }
        return exists;
    }

    template <typename T, EventType event_type, class AssociatedClass>
    static void registerSubscriber(AssociatedClass* obj_ptr, void (AssociatedClass::*callback_fn_ptr)(T)) {
        std::function<void(T)> callback_fn = std::bind(callback_fn_ptr, obj_ptr, std::placeholders::_1);
        Subscriber<T, AssociatedClass>* new_subscriber = new Subscriber<T, AssociatedClass>(callback_fn, event_type, obj_ptr);
        event_id_type event_id = EventId::get_unique_id<T>(event_type);

        bool exists = subscriberExists(new_subscriber, event_id);
        if (!exists)
            EventHandler::subscribers_args[event_id].push_back(new_subscriber);

    }

    template <EventType event_type, class AssociatedClass>
    static void registerSubscriber(AssociatedClass* obj_ptr, void (AssociatedClass::*callback_fn_ptr)(void)) {
        std::function<void()> callback_fn = std::bind(callback_fn_ptr, obj_ptr);
        Subscriber<void, AssociatedClass>* new_subscriber = new Subscriber<void, AssociatedClass>(callback_fn, event_type, obj_ptr);
        event_id_type event_id = EventId::get_unique_id<void>(event_type);

        bool exists = subscriberExists(new_subscriber,  event_id);
        if (!exists)
            EventHandler::subscribers_args[event_id].push_back(new_subscriber);

    }



    template <typename T, EventType event_type, class AssociatedClass>
    static void unsubscribe(AssociatedClass* obj, void (AssociatedClass::*fn)(T)) {
        event_id_type event_id = EventId::get_unique_id<T>(event_type);
        std::vector<SubscriberBase*>& cur_vec = EventHandler::subscribers_args[event_id];

        int i = 0;
        int i_to_remove = 0;
        bool found = false;
        for (SubscriberBase* subscriber : cur_vec) {
            Subscriber<T, AssociatedClass>* cast = static_cast<Subscriber<T, AssociatedClass>*>(subscriber);
            
            if(cast->obj_ptr) 
                if (cast->obj_ptr == obj){
                    i_to_remove = i;
                    found = true;
                }
                

            ++i;
        }

        if (!found) {
            std::cerr << "The class isn't event subscribed" << std::endl;
            return;
        }
        SubscriberBase* element_to_remove = cur_vec[i_to_remove];
        cur_vec.erase(cur_vec.begin() + i_to_remove);
        delete(element_to_remove);
    }

    template <EventType event_type, class AssociatedClass>
    static void unsubscribe(AssociatedClass* obj, void (AssociatedClass::*fn)(void)) {
        event_id_type event_id = EventId::get_unique_id<void>(event_type);
        std::vector<SubscriberBase*>& cur_vec = EventHandler::subscribers_args[event_id];

        int i = 0;
        int i_to_remove = 0;
        bool found = false;
        for (auto& subscriber : cur_vec) {
            Subscriber<void, AssociatedClass>* cast = static_cast<Subscriber<void, AssociatedClass>*>(subscriber);

            if (cast->obj_ptr)
                if (cast->obj_ptr == obj) {
                    i_to_remove = i;
                    found = true;
                }

            ++i;
        }

        if (!found) {
            std::cerr << "The class isn't event subscribed" << std::endl;
            return;
        }

        SubscriberBase* element_to_remove = cur_vec[i_to_remove];
        cur_vec.erase(cur_vec.begin() + i_to_remove);
        delete(element_to_remove);

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
