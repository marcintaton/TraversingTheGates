#include "GameLoop.h"

#include "global/GlobalGLData.h"

// move this somewhere else
#include "entities/Camera.h"
#include "systems/GameSystems.h"

void GameLoop::initialize()
{
    ECS::ECEngine::get_instance().create_entity<Camera>();
    ECS::SystemEngine::get_instance().create_active_system<Renderer>();
    ECS::SystemEngine::get_instance().create_independent_system<LevelSetup>();
    ECS::SystemEngine::get_instance()
        .create_independent_system<LevelGenerationManager>();
    ECS::SystemEngine::get_instance()
        .create_independent_system<TextureManager>();
    ECS::SystemEngine::get_instance()
        .create_independent_system<ShaderManager>();
    ECS::SystemEngine::get_instance().create_independent_system<UserInput>();
    ECS::SystemEngine::get_instance()
        .create_independent_system<PlayerMovement>();

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