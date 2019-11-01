#pragma once
#include "event.h"
#include <map>
#include <variant>

#define EVENT_VARIANTS std::variant<Event<int, int>, Event<bool>, Event<>>

class EventManager
{
  private:
    std::map<EventType, EVENT_VARIANTS> events;

  public:
    EventManager()
    {
        events[EventType::on_end_of_level_reached] =
            Event<int, int>(EventType::on_end_of_level_reached);
        events[EventType::on_game_saved] =
            Event<bool>(EventType::on_game_saved);
        events[EventType::on_new_game_started] =
            Event<>(EventType::on_new_game_started);
        events[EventType::on_player_death] =
            Event<int, int>(EventType::on_player_death);
    }

    template<typename... T_args>
    Event<T_args...>& get_event(EventType type)
    {
        return std::get<Event<T_args...>>(events[type]);
    }
};