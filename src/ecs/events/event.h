#pragma once
#include "eventSubscriptionBind.h"
#include "eventType.h"
#include "trackedFunction.h"
#include <algorithm>
#include <functional>
#include <vector>

template<typename... T_args>
class Event
{
  private:
    size_t tracking_function_index = 0;
    std::vector<TrackedFunction<T_args...>> listeners;

  public:
    const EventType event_type;

    Event() : event_type(EventType::error_type) {}
    Event(EventType type) : event_type(type) {}

    EventSubscriptionBind<T_args...>
    subscribe(std::function<void(T_args...)> subscriber)
    {
        TrackedFunction<T_args...> identified_subscriber =
            TrackedFunction<T_args...>(
                {.tracking_id = ++tracking_function_index,
                 .function = subscriber});
        listeners.push_back(identified_subscriber);

        EventSubscriptionBind<T_args...> bind = {.subscribed_event = *this,
                                                 .tracked_listener_id =
                                                     tracking_function_index};

        return bind;
    }

    void Unsubscribe(size_t bind_index)
    {
        auto erase_iterator = std::find_if(
            listeners.begin(), listeners.end(),
            [&](const auto& val) { return val.tracking_id == bind_index; });

        listeners.erase(erase_iterator);
    }

    void Invoke(T_args... args)
    {
        for (auto identifier : listeners) {
            identifier.function(std::forward<T_args>(args)...);
        }
    }
};

template<typename... T_args>
bool operator==(const Event<T_args...>& a, const Event<T_args...>& b)
{
    return a.event_type == b.event_type;
}