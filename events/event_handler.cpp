#include "event_handler.hpp"
#include "event.h"
#include <type_traits>

#define NUM_OF_EVENTS 50

std::map<event_id_type, std::queue<EventBase*>> EventHandler::event_args_queue = {};
std::map<event_id_type, std::vector<SubscriberBase*>> EventHandler::subscribers_args = {};

void EventHandler::pollEvents() {

    for (auto& [key, queue]: EventHandler::event_args_queue) {
        int que_size = queue.size();

        int count = 0;
        while (count < que_size) {

            std::vector<SubscriberBase*>& cur_subscribers = EventHandler::subscribers_args[key];

            for (SubscriberBase* const& subscriber : cur_subscribers) {
                subscriber->callback(key);
            }

            EventBase* cur_event = queue.front();
            queue.pop();
            delete cur_event;
            count++;
        }
        
    }
}

void EventHandler::emitEvent(Event<void> event) {
    Event<void>* event_ptr = new Event<void>(event.event_type);
    event_id_type event_id = EventId::get_unique_id<void>(event.event_type);
    EventHandler::event_args_queue[event_id].push(event_ptr);
}

std::size_t EventId::counter = 0;



