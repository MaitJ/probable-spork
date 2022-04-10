#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <vector>
#include <queue>
#include <functional>
#include "events.hpp"


struct Subscriber {
    void* object;
    std::function<void()> callback_fn;

public:
    Subscriber(void* object, std::function<void()> callback_fn) : object{object}, callback_fn {callback_fn} {}
};

class EventHandler {

public:
    static std::queue<Events> event_queue;
    static std::vector<Subscriber>* subscribers;
    static void pollEvents();
    static void registerSubscriber(void* object, Events event, std::function<void()> callback);
    static void emitEvent(Events event);

    template <typename T>
    static void emitEvent(Events event, T val);
};

#endif
