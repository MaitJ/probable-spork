#include "event_handler.hpp"
#include "event.h"

void EventHandler::registerSubscriber(void* object, Events event, std::function<void()> callback) {
    Subscriber new_subscriber(object, callback);
    EventHandler::subscribers[event].insert(subscribers[event].end(), new_subscriber);
}

std::vector<Subscriber>* EventHandler::subscribers = new std::vector<Subscriber>[Events::COUNT];
std::queue<Events> EventHandler::event_queue = {};

void EventHandler::pollEvents() {
    for (int i = 0; i < EventHandler::event_queue.size(); ++i) {
        Events poll_event = EventHandler::event_queue.front();
        EventHandler::event_queue.pop();

        for (int j = 0; j < EventHandler::subscribers[poll_event].size(); ++j) {
            EventHandler::subscribers[poll_event][j].callback_fn();
        }
    }
}

void EventHandler::emitEvent(Events event) {
    EventHandler::event_queue.push(event);
}

template <typename T>
static void emitEvent(Events event, T val) {
    
}
