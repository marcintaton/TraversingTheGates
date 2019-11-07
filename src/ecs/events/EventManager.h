#pragma once

#include <memory>
#include <type_traits>
#include <unordered_map>

#include "../../utility/type.h"
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
            return (dispatchers[utility::type::get_type_id<Event<T>>()]) !=
                   nullptr;
        }

        template<class T>
        void create_dispatcher()
        {
            dispatchers[utility::type::get_type_id<Event<T>>()] =
                std::make_shared<EventDispatcher<T>>();
        }

      public:
        template<class T>
        void send_event(T* event)
        {
            if (is_dispatcher_present<T>()) {
                (dispatchers[utility::type::get_type_id<Event<T>>()])
                    ->dispatch(event);
            }
        }

        template<class T>
        void add_listener(IEventDelegate* delegate)
        {
            if (is_event_type_valid<T>()) {
                if (!is_dispatcher_present<T>()) {
                    create_dispatcher<T>();
                }

                dispatchers[delegate->get_event_type_id()]->add_delegate(
                    delegate);
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