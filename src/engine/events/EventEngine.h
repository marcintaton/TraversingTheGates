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
class EventEngine
{
    // Singleton
  public:
    static EventEngine& get_instance()
    {
        static EventEngine instance;
        return instance;
    }

  private:
    EventEngine() {}
    EventEngine(EventEngine const&) = delete;
    void operator=(EventEngine const&) = delete;

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

            spdlog::info("Event::EventEngine::send_event - Sending event {0}",
                         Utility::Type::get_type_name<T>());
        }
    }

    template<class T>
    void add_listener(IEventDelegate* delegate)
    {

        if (is_event_type_valid<T>()) {
            if (Utility::Type::get_type_id<Event<T>>() !=
                delegate->get_event_type_id()) {
                spdlog::error(
                    "Event::EventEngine::add_listener - Type mismatch "
                    "between passed template type and delegate type");
                return;
            }
            if (!is_dispatcher_present<T>()) {
                create_dispatcher<T>();
            }

            dispatchers[delegate->get_event_type_id()]->add_delegate(delegate);
        } else {
            spdlog::error("Event::EventEngine::add_listener - Type is not "
                          "event");
        }
    }

    template<class T>
    void remove_listener(IEventDelegate* delegate)
    {
        if (is_dispatcher_present<T>()) {
            if (Utility::Type::get_type_id<Event<T>>() !=
                delegate->get_event_type_id()) {
                spdlog::error(
                    "Event::EventEngine::remove_listener - Type mismatch "
                    "between passed template type and delegate type");
                return;
            }
            dispatchers[delegate->get_event_type_id()]->remove_delegate(
                delegate);
        } else {
            spdlog::error("Event::EventEngine::remove_listener - dispatcher "
                          "was never created");
        }
    }
};
}; // namespace Event