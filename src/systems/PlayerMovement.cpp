#include "PlayerMovement.h"

#include "../others/Direction.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

PlayerMovement::PlayerMovement()
{
    movement_delegate = Event::EventDelegate<PlayerMovement, KeyPress>(
        this, &PlayerMovement::receive_key_input);

    expected_keys = {GLFW_KEY_W, GLFW_KEY_UP,    GLFW_KEY_S, GLFW_KEY_DOWN,
                     GLFW_KEY_D, GLFW_KEY_RIGHT, GLFW_KEY_A, GLFW_KEY_LEFT};
}

void PlayerMovement::subscribe()
{
    Event::EventEngine::get_instance().add_listener<KeyPress>(
        &movement_delegate);
}
void PlayerMovement::unsubscribe()
{

    Event::EventEngine::get_instance().remove_listener<KeyPress>(
        &movement_delegate);
}

void PlayerMovement::on_enable()
{
    subscribe();
}

void PlayerMovement::on_disable()
{
    unsubscribe();
}

void PlayerMovement::receive_key_input(const KeyPress* event)
{

    if (std::find(expected_keys.begin(), expected_keys.end(),
                  event->key_code) != expected_keys.end()) {

        if (!event->is_reserved) {
            move_player(event->key_code);
        }
    }
}

void PlayerMovement::move_player(int key_code)
{

    if (player_transform == nullptr) {
        player_id = ECS::ECEngine::get_instance()
                        .get_entities_of_type<Player>()[0]
                        ->get_entity_id();
        player_transform =
            ECS::ECEngine::get_instance().get_component<Transform>(player_id);
    }

    auto player_position = ECS::SystemEngine::get_instance()
                               .get_independent_system<LevelMap>()
                               ->find_position(player_id);
    auto orig_position = player_position;

    bool did_move = false;
    glm::vec3 move_vec = glm::vec3(0, 0, 0);
    Direction dir;

    if (key_code == GLFW_KEY_W || key_code == GLFW_KEY_UP) {
        player_position.j += 1;
        move_vec += glm::vec3(0, 1, 0);
        did_move = true;
        dir = Direction::UP;
    }
    if (key_code == GLFW_KEY_S || key_code == GLFW_KEY_DOWN) {
        player_position.j += -1;
        move_vec += glm::vec3(0, -1, 0);
        did_move = true;
        dir = Direction::DOWN;
    }
    if (key_code == GLFW_KEY_D || key_code == GLFW_KEY_RIGHT) {
        player_position.i += 1;
        move_vec += glm::vec3(1, 0, 0);
        did_move = true;
        dir = Direction::RIGHT;
    }
    if (key_code == GLFW_KEY_A || key_code == GLFW_KEY_LEFT) {
        player_position.i += -1;
        move_vec += glm::vec3(-1, 0, 0);
        did_move = true;
        dir = Direction::LEFT;
    }

    if (did_move && ECS::SystemEngine::get_instance()
                        .get_independent_system<LevelMap>()
                        ->is_tile_available(player_position)) {

        player_transform->position += move_vec;
        ECS::SystemEngine::get_instance()
            .get_independent_system<LevelMap>()
            ->move_dynamic_element(player_id, player_position);

        PlayerMoved player_move_event;
        Event::EventEngine::get_instance().send_event<PlayerMoved>(
            &player_move_event);

        ObjectMoved obj_move_event = ObjectMoved {.object_id = player_id,
                                                  .old_pos = orig_position,
                                                  .new_pos = player_position,
                                                  .new_direction = dir};
        Event::EventEngine::get_instance().send_event<ObjectMoved>(
            &obj_move_event);

        TurnEnd turn_end_event;
        Event::EventEngine::get_instance().send_event<TurnEnd>(&turn_end_event);
    }
}