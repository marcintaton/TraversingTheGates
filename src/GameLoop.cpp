#include "GameLoop.h"

#include "global/GlobalGLData.h"

void GameLoop::initialize() {}

void GameLoop::run_game_loop()
{

    while (
        !glfwWindowShouldClose(Global::GlobalGLData::get_instance().window)) {

        // update systems
        system_update_invoker.update_systems();

        // register events
        glfwPollEvents();

        // update deltatime
        timer.update_timer();
    }
}