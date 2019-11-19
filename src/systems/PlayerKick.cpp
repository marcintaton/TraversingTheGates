#include "PlayerKick.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

PlayerKick::PlayerKick()
{
    kick_delegate =
        Event::EventDelegate<PlayerKick, KeyPress>(this, &PlayerKick::kick);

    direction_keys = {GLFW_KEY_W, GLFW_KEY_UP,    GLFW_KEY_S, GLFW_KEY_DOWN,
                      GLFW_KEY_D, GLFW_KEY_RIGHT, GLFW_KEY_A, GLFW_KEY_LEFT};
}

void PlayerKick::subscribe()
{
    Event::EventEngine::get_instance().add_listener<KeyPress>(&kick_delegate);
}

void PlayerKick::unsubscribe()
{
    Event::EventEngine::get_instance().remove_listener<KeyPress>(
        &kick_delegate);
}

void PlayerKick::on_enable()
{
    subscribe();
}

void PlayerKick::on_disable()
{
    unsubscribe();
}

void PlayerKick::kick(const KeyPress* event)
{
    if (player_id == 0) {
        player_id = ECS::ECEngine::get_instance()
                        .get_entities_of_type<Player>()[0]
                        ->get_entity_id();
    }

    if (!is_in_kick_state && event->key_code == GLFW_KEY_K) {
        enter_kick_state();
    } else if (is_in_kick_state) {
        resolve_keys_in_kick_state(event);
    }
}

void PlayerKick::enter_kick_state()
{
    is_in_kick_state = true;
    SetKeysReservation event =
        SetKeysReservation {.key_codes = direction_keys, .to_state = 1};
    Event::EventEngine::get_instance().send_event<SetKeysReservation>(&event);
}

void PlayerKick::resolve_keys_in_kick_state(const KeyPress* event)
{

    bool did_kick = false;
    auto key_code = event->key_code;
    auto level_map =
        ECS::SystemEngine::get_instance().get_independent_system<LevelMap>();

    ECS::EntityId kicked_entity = 0;
    if (key_code == GLFW_KEY_W || key_code == GLFW_KEY_UP) {
        kicked_entity = level_map->get_neighbour_id(player_id, Direction::UP);
        spdlog::info("Kicked up");
        did_kick = true;
    }
    if (key_code == GLFW_KEY_S || key_code == GLFW_KEY_DOWN) {
        kicked_entity = level_map->get_neighbour_id(player_id, Direction::DOWN);
        spdlog::info("Kicked down");
        did_kick = true;
    }
    if (key_code == GLFW_KEY_D || key_code == GLFW_KEY_RIGHT) {
        kicked_entity =
            level_map->get_neighbour_id(player_id, Direction::RIGHT);
        spdlog::info("Kicked right");
        did_kick = true;
    }
    if (key_code == GLFW_KEY_A || key_code == GLFW_KEY_LEFT) {
        kicked_entity = level_map->get_neighbour_id(player_id, Direction::LEFT);
        spdlog::info("Kicked left");
        did_kick = true;
    }

    if (did_kick) {
        Kick kick_event = Kick {.source = player_id, .target = kicked_entity};
        Event::EventEngine::get_instance().send_event<Kick>(&kick_event);

        TurnEnd turn_end_event;
        Event::EventEngine::get_instance().send_event<TurnEnd>(&turn_end_event);
    }

    SetKeysReservation key_reserve_event =
        SetKeysReservation {.key_codes = direction_keys, .to_state = 0};
    Event::EventEngine::get_instance().send_event<SetKeysReservation>(
        &key_reserve_event);

    is_in_kick_state = false;
}
