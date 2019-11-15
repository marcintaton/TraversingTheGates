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
    if (!is_in_kick_state && event->key_code == GLFW_KEY_K) {
        is_in_kick_state = true;
        SetKeysReservation event =
            SetKeysReservation {.key_codes = direction_keys, .to_state = 1};
        Event::EventEngine::get_instance().send_event<SetKeysReservation>(
            &event);
    } else if (is_in_kick_state) {
        auto key_code = event->key_code;
        if (key_code == GLFW_KEY_W || key_code == GLFW_KEY_UP) {
            spdlog::info("Kicked up");
        }
        if (key_code == GLFW_KEY_S || key_code == GLFW_KEY_DOWN) {
            spdlog::info("Kicked down");
        }
        if (key_code == GLFW_KEY_D || key_code == GLFW_KEY_RIGHT) {
            spdlog::info("Kicked right");
        }
        if (key_code == GLFW_KEY_A || key_code == GLFW_KEY_LEFT) {
            spdlog::info("Kicked left");
        }

        SetKeysReservation event =
            SetKeysReservation {.key_codes = direction_keys, .to_state = 0};
        Event::EventEngine::get_instance().send_event<SetKeysReservation>(
            &event);

        is_in_kick_state = false;
    }
}
