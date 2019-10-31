#pragma once
#include "event.h"

class EventManager
{
  public:
    Event<int, int> some_event_1 =
        Event<int, int>(EventType::on_end_of_level_reached);
    Event<bool> some_event_2 = Event<bool>(EventType::on_game_saved);
    Event<> some_event_3 = Event<>(EventType::on_new_game_started);
    Event<int, int> some_event_4 = Event<int, int>(EventType::on_player_death);
};