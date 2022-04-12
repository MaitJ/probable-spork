#include "event_handler.hpp"
#include "event.h"
#include <type_traits>

#define NUM_OF_EVENTS 50


void EventHandler::registerSubscriber(Event event, std::function<void()> callback) {
    Subscriber new_subscriber(callback);
    EventHandler::subscribers[event.event_type].push_back(new_subscriber);
}


std::map<int, std::vector<Subscriber>> EventHandler::subscribers = {};
std::queue<Event> EventHandler::event_queue = {};

std::map<unique_id_type, std::queue<Event*>> EventHandler::event_args_queue = {};
std::map<unique_id_type, std::vector<SubscriberBase*>> EventHandler::subscribers_args = {};

void EventHandler::pollEvents() {
    for (int i = 0; i < EventHandler::event_queue.size(); ++i) {
        Event poll_event = EventHandler::event_queue.front();
        EventHandler::event_queue.pop();
        for (int j = 0; j < EventHandler::subscribers.size(); ++j) {
            EventHandler::subscribers[poll_event.event_type][j].callback();
        }
    }

    for (auto it = EventHandler::event_args_queue.begin(); it != EventHandler::event_args_queue.end(); ++it) {
        std::queue<Event*>& cur_queue = it->second;
        for (int i = 0; i < cur_queue.size(); ++i) {
            std::vector<SubscriberBase*>& cur_subscribers = EventHandler::subscribers_args[it->first];
            for (int j = 0; j < cur_subscribers.size(); ++j) {
                cur_subscribers[j]->callback();
            }
            Event* cur_event = cur_queue.front();
            cur_queue.pop();
            delete cur_event;
        }
    }
}

void Subscriber::callback() {
    this->callback_fn();
}


void EventHandler::emitEvent(Event event) {
    EventHandler::event_queue.push(event);
}

SubscriberBase::~SubscriberBase() {}
void SubscriberBase::callback() {}


