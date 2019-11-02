#pragma once
#include "event.h"
#include "eventSubscriptionBind.h"
#include <any>
#include <functional>
#include <iostream>
#include <vector>

class IEventSubscriber
{
  private:
    std::vector<std::any> subscription_binds;

  public:
    template<typename... T_args>
    void subscribe(Event<T_args...>& to_event,
                   std::function<void(T_args...)> function)
    {
        EventSubscriptionBind<T_args...> bind = to_event.subscribe(function);
        subscription_binds.push_back(bind);
    }

    template<typename... T_args>
    void unsubscribe(Event<T_args...>& from_event)
    {
        auto bind_iterator = std::find_if(
            subscription_binds.begin(), subscription_binds.end(),
            [&](const auto& bind) {
                try {
                    return (std::any_cast<EventSubscriptionBind<T_args...>>(
                                bind))
                               .subscribed_event == from_event;
                } catch (const std::bad_any_cast& e) {
                    return false;
                }
            });

        try {
            from_event.Unsubscribe(
                (std::any_cast<EventSubscriptionBind<T_args...>>(
                     *bind_iterator))
                    .tracked_listener_id);
            subscription_binds.erase(bind_iterator);
        } catch (const std::exception& e) {
            std::cout
                << "ECS::EVENT_ENGINE::IEVENTSUBSCRIBER::UNSUBSCRIBE::FAIL"
                << " Event not subscribed" << std::endl;
        }
    }
};