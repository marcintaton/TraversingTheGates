#include "PlayerInteraction.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

PlayerInteraction::PlayerInteraction()
{
    interaction_delegate = Event::EventDelegate<PlayerInteraction, KeyPress>(
        this, &PlayerInteraction::interact);

    direction_keys = {GLFW_KEY_W, GLFW_KEY_UP,    GLFW_KEY_S, GLFW_KEY_DOWN,
                      GLFW_KEY_D, GLFW_KEY_RIGHT, GLFW_KEY_A, GLFW_KEY_LEFT};
}

void PlayerInteraction::subscribe()
{
    Event::EventEngine::get_instance().add_listener<KeyPress>(
        &interaction_delegate);
}

void PlayerInteraction::unsubscribe()
{
    Event::EventEngine::get_instance().remove_listener<KeyPress>(
        &interaction_delegate);
}

void PlayerInteraction::on_enable()
{
    subscribe();
}

void PlayerInteraction::on_disable()
{
    unsubscribe();
}

void PlayerInteraction::interact(const KeyPress* event)
{
    if (player_id == 0) {
        player_id = ECS::ECEngine::get_instance()
                        .get_entities_of_type<Player>()[0]
                        ->get_entity_id();
    }

    if (!is_in_kick_state && event->key_code == GLFW_KEY_K) {
        enter_kick_state();
    } else if (!is_in_use_state && event->key_code == GLFW_KEY_U) {
        enter_use_state();
    } else if (is_in_kick_state) {
        resolve_keys_in_kick_state(event);
    } else if (is_in_use_state) {
        resolve_keys_in_use_state(event);
    }
}

void PlayerInteraction::enter_kick_state()
{
    is_in_kick_state = true;
    SetKeysReservation event =
        SetKeysReservation {.key_codes = direction_keys, .to_state = 1};
    Event::EventEngine::get_instance().send_event<SetKeysReservation>(&event);
}

void PlayerInteraction::enter_use_state()
{
    is_in_use_state = true;
    SetKeysReservation event =
        SetKeysReservation {.key_codes = direction_keys, .to_state = 1};
    Event::EventEngine::get_instance().send_event<SetKeysReservation>(&event);
}

void PlayerInteraction::resolve_keys_in_kick_state(const KeyPress* event)
{
    auto interacted_entity = get_interacted_entity_id(event);

    if (interacted_entity != 0) {
        Kick kick_event =
            Kick {.source = player_id, .target = interacted_entity};
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

void PlayerInteraction::resolve_keys_in_use_state(const KeyPress* event)
{
    auto interacted_entity = get_interacted_entity_id(event);

    if (interacted_entity != 0) {
        Use use_event = Use {.source = player_id, .target = interacted_entity};
        Event::EventEngine::get_instance().send_event<Use>(&use_event);

        TurnEnd turn_end_event;
        Event::EventEngine::get_instance().send_event<TurnEnd>(&turn_end_event);
    }

    SetKeysReservation key_reserve_event =
        SetKeysReservation {.key_codes = direction_keys, .to_state = 0};
    Event::EventEngine::get_instance().send_event<SetKeysReservation>(
        &key_reserve_event);

    is_in_use_state = false;
}

ECS::EntityId PlayerInteraction::get_interacted_entity_id(const KeyPress* event)
{
    auto key_code = event->key_code;
    auto level_map =
        ECS::SystemEngine::get_instance().get_independent_system<LevelMap>();

    ECS::EntityId interacted_entity = 0;
    if (key_code == GLFW_KEY_W || key_code == GLFW_KEY_UP) {
        interacted_entity =
            level_map->get_neighbour_id(player_id, Direction::UP);
    }
    if (key_code == GLFW_KEY_S || key_code == GLFW_KEY_DOWN) {
        interacted_entity =
            level_map->get_neighbour_id(player_id, Direction::DOWN);
    }
    if (key_code == GLFW_KEY_D || key_code == GLFW_KEY_RIGHT) {
        interacted_entity =
            level_map->get_neighbour_id(player_id, Direction::RIGHT);
    }
    if (key_code == GLFW_KEY_A || key_code == GLFW_KEY_LEFT) {
        interacted_entity =
            level_map->get_neighbour_id(player_id, Direction::LEFT);
    }

    return interacted_entity;
}
