#include "event_handler.hpp"
#include "event.h"
#include <type_traits>

#define NUM_OF_EVENTS 50

template <typename T>
void EventHandler::registerSubscriber(EventArgs<T> event, std::function<void(T)> callback) {

    SubscriberArgs<T> new_subscriber = new SubscriberArgs<T>(callback);
    EventHandler::subscribers_args[EventId<T>::get_unique_id()].push_back(new_subscriber);
}

void EventHandler::registerSubscriber(Event event, std::function<void()> callback) {
    Subscriber new_subscriber(callback);
    EventHandler::subscribers[event.event_type].push_back(new_subscriber);
}


std::map<int, std::vector<Subscriber>> EventHandler::subscribers = {};
std::queue<Event> EventHandler::event_queue = {};

void EventHandler::pollEvents() {
    for (int i = 0; i < EventHandler::event_queue.size(); ++i) {
        Event poll_event = EventHandler::event_queue.front();
        EventHandler::event_queue.pop();
        for (int j = 0; j < EventHandler::subscribers.size(); ++j) {
            EventHandler::subscribers[poll_event.event_type].callback();
        }
    }
}

void Subscriber::callback() {
    this->callback_fn();
}

template <typename T>
void SubscriberArgs<T>::callback() {
    this->callback_fn();
}

void EventHandler::emitEvent(EventBase event) {
    EventHandler::event_queue.push(&event);
}

template <typename T>
static void emitEvent(Event<T> event) {
    EventHandler::event_queue.push(&event);
}


template <typename T>
int EventId::next_value() {
}
