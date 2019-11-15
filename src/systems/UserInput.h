#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <bitset>

#include "../engine/GameEngine.h"
#include "../events/GameEvents.h"

class UserInput : public ECS::System::IndependentSystem<UserInput>
{
  private:
    std::bitset<1024> keys;
    std::bitset<1024> reserved_keys;

    Event::EventDelegate<UserInput, SetKeysReservation> keys_reservation;

    void setup_callbacks();
    static void key_callback(GLFWwindow* window, int key, int scancode,
                             int action, int mods);
    void set_key_state(int key_code, int action);
    void set_keys_reservation(const SetKeysReservation* event);

  public:
    UserInput();
};