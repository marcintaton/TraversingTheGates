#include "PlayerMovement.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

PlayerMovement::PlayerMovement()
{
    movement_delegate = Event::EventDelegate<PlayerMovement, OnKeyPress>(
        this, &PlayerMovement::receive_key_input);

    expected_keys = {GLFW_KEY_W, GLFW_KEY_UP,    GLFW_KEY_S, GLFW_KEY_DOWN,
                     GLFW_KEY_D, GLFW_KEY_RIGHT, GLFW_KEY_A, GLFW_KEY_LEFT};
}

void PlayerMovement::subscribe()
{
    Event::EventEngine::get_instance().add_listener<OnKeyPress>(
        &movement_delegate);
}
void PlayerMovement::unsubscribe()
{

    Event::EventEngine::get_instance().remove_listener<OnKeyPress>(
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

void PlayerMovement::receive_key_input(const OnKeyPress* event)
{

    if (std::find(expected_keys.begin(), expected_keys.end(),
                  event->key_code) != expected_keys.end()) {

        move_player(event->key_code);
    }
}

void PlayerMovement::move_player(int key_code)
{

    auto player_id = ECS::ECEngine::get_instance()
                         .get_entities_of_type<Player>()[0]
                         ->get_entity_id();
    auto player_transform =
        ECS::ECEngine::get_instance().get_component<Transform>(player_id);

    if (key_code == GLFW_KEY_W || key_code == GLFW_KEY_UP) {
        player_transform->position += glm::vec3(0, 1, 0);
    }
    if (key_code == GLFW_KEY_S || key_code == GLFW_KEY_DOWN) {
        player_transform->position += glm::vec3(0, -1, 0);
    }
    if (key_code == GLFW_KEY_D || key_code == GLFW_KEY_RIGHT) {
        player_transform->position += glm::vec3(1, 0, 0);
    }
    if (key_code == GLFW_KEY_A || key_code == GLFW_KEY_LEFT) {
        player_transform->position += glm::vec3(-1, 0, 0);
    }
}