#include "event_handler.hpp"
#include "event.h"
#include <type_traits>

#define NUM_OF_EVENTS 50

std::map<event_id_type, std::queue<EventBase*>> EventHandler::event_args_queue = {};
std::map<event_id_type, std::vector<SubscriberBase*>> EventHandler::subscribers_args = {};

void EventHandler::pollEvents() {
    for (auto it = EventHandler::event_args_queue.begin(); it != EventHandler::event_args_queue.end(); ++it) {
        std::queue<EventBase*>& cur_queue = it->second;
        for (int i = 0; i < cur_queue.size(); ++i) {
            //Pass the event_id to calllback, so callback can find the right event to forward
            //event_args_queue and subscriber_args are so event_id_type for Event<int>(EventType::MOVE_LEFT) == Subscriber<int, EventType::MOVE_LEFT>
            std::vector<SubscriberBase*>& cur_subscribers = EventHandler::subscribers_args[it->first];

            for (int j = 0; j < cur_subscribers.size(); ++j) {
                cur_subscribers[j]->callback(it->first);
            }

            EventBase* cur_event = cur_queue.front();
            cur_queue.pop();
            delete cur_event;
        }
    }
}

void EventHandler::emitEvent(Event<void> event) {
    Event<void>* event_ptr = new Event<void>(event.event_type);
    event_id_type event_id = EventId::get_unique_id<void>(event.event_type);
    EventHandler::event_args_queue[event_id].push(event_ptr);
}

std::size_t EventId::counter = 0;



