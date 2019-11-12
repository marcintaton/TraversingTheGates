#include "UserInput.h"

#include "../events/GameEvents.h"
#include "../global/GlobalGLData.h"

UserInput::UserInput()
{
    setup_callbacks();
}

void UserInput::setup_callbacks()
{

    glfwSetKeyCallback(Global::GlobalGLData::get_instance().window,
                       key_callback);
}

void UserInput::set_key_state(int key_code, int action)
{
    keys[key_code] = action;
}

void UserInput::key_callback(GLFWwindow* window, int key, int scancode,
                             int action, int mods)
{

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS || action == GLFW_RELEASE) {
            auto user_input = ECS::SystemEngine::get_instance()
                                  .get_independent_system<UserInput>();
            user_input->set_key_state(key, action);
            if (action == GLFW_PRESS) {
                KeyPress event {.key_code = key};
                Event::EventEngine::get_instance().send_event<KeyPress>(&event);
            } else if (action == GLFW_RELEASE) {
                KeyRelease event {.key_code = key};
                Event::EventEngine::get_instance().send_event<KeyRelease>(
                    &event);
            }
        }
    }
}