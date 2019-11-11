#include "GameLoop.h"

#include "global/GlobalGLData.h"

// move this somewhere else
#include "systems/LevelSetup.h"
#include "systems/Renderer.h"
#include "systems/ShaderManager.h"
#include "systems/TextureManager.h"

void GameLoop::initialize()
{

    ECS::SystemEngine::get_instance().create_active_system<Renderer>();
    ECS::SystemEngine::get_instance().create_independent_system<LevelSetup>();
    ECS::SystemEngine::get_instance()
        .create_independent_system<TextureManager>();
    ECS::SystemEngine::get_instance()
        .create_independent_system<ShaderManager>();

    OnLoadNewLevel load_level_event;
    Event::EventEngine::get_instance().send_event<OnLoadNewLevel>(
        &load_level_event);
}

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