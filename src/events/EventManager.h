#pragma once

#include <memory>
#include <type_traits>
#include <unordered_map>

#include "../utility/Logging.h"
#include "../utility/Type.h"
#include "Event.h"
#include "EventDispatcher.h"

namespace Event
{
class EventManager
{
    // Singleton
  public:
    static EventManager& get_instance()
    {
        static EventManager instance;
        return instance;
    }

  private:
    EventManager() {}
    EventManager(EventManager const&) = delete;
    void operator=(EventManager const&) = delete;

    //

  private:
    std::unordered_map<EventTypeId, std::shared_ptr<IEventDispatcher>>
        dispatchers;

    template<class T>
    bool is_event_type_valid()
    {
        return std::is_base_of<IEvent, T>();
    }

    template<class T>
    bool is_dispatcher_present()
    {
        return (dispatchers[Utility::Type::get_type_id<Event<T>>()]) != nullptr;
    }

    template<class T>
    void create_dispatcher()
    {
        dispatchers[Utility::Type::get_type_id<Event<T>>()] =
            std::make_shared<EventDispatcher<T>>();
    }

  public:
    template<class T>
    void send_event(T* event)
    {
        if (is_dispatcher_present<T>()) {
            (dispatchers[Utility::Type::get_type_id<Event<T>>()])
                ->dispatch(event);

            spdlog::info("Event::EventManager::send_event - Sending event {0}",
                         Utility::Type::get_type_name<T>());
        }
    }

    template<class T>
    void add_listener(IEventDelegate* delegate)
    {
        if (is_event_type_valid<T>()) {
            if (!is_dispatcher_present<T>()) {
                create_dispatcher<T>();
            }

            dispatchers[delegate->get_event_type_id()]->add_delegate(delegate);
        } else {
            spdlog::warn("Event::EventManager::add_listener - Type is not "
                         "event. Aborting");
        }
    }

    template<class T>
    void remove_listener(IEventDelegate* delegate)
    {
        if (is_dispatcher_present<T>()) {
            dispatchers[delegate->get_event_type_id()]->remove_delegate(
                delegate);
        }
    }
};
}; // namespace Event