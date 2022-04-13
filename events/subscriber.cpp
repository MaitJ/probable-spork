#include "subscriber.hpp"

SubscriberBase::SubscriberBase(EventType event_type) : event_type{event_type} {}

void Subscriber<void>::callback(event_id_type event_id) {
    this->callback_fn();
}

