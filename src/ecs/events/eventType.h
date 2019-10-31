#pragma once

enum class EventType {
    error_type,
    on_player_death,
    on_level_loaded,
    on_new_game_started,
    on_game_saved,
    on_end_of_level_reached
};