#include "subscriber.hpp"

SubscriberBase::SubscriberBase(EventType event_type) : event_type{event_type} {}

/*
template <class AssociatedClass>
void Subscriber<void, AssociatedClass>::callback(event_id_type event_id) {
    this->callback_fn();
}
*/
