#include "LevelSetup.h"

#include "../components/GameComponents.h"
#include "../entities/Camera.h"
#include "../systems/GameSystems.h"
#include "../systems/LevelGenerationManager.h"

LevelSetup::LevelSetup()
{
    load_level_delegate = Event::EventDelegate<LevelSetup, LoadNewLevel>(
        this, &LevelSetup::setup_new_level);
}

void LevelSetup::on_enable()
{
    Event::EventEngine::get_instance().add_listener<LoadNewLevel>(
        &load_level_delegate);
}

void LevelSetup::on_disable()
{
    Event::EventEngine::get_instance().remove_listener<LoadNewLevel>(
        &load_level_delegate);
}

void LevelSetup::setup_new_level(const LoadNewLevel* event)
{
    auto level_gen_man = ECS::SystemEngine::get_instance()
                             .get_independent_system<LevelGenerationManager>();

    auto level_data = level_gen_man->generate_dungeon_level();

    ECS::SystemEngine::get_instance()
        .get_independent_system<LevelMap>()
        ->init_current_level(level_data);

    ECS::SystemEngine::get_instance()
        .get_independent_system<CameraMovement>()
        ->center_on_player();
}