#pragma once
#include "event.hpp"
#include <algorithm>

template<typename... T_args>
struct EventSubscriptionBind {
    Event<T_args...> subscribed_event;
    size_t tracked_listener_id;
};