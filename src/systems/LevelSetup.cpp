#include "LevelSetup.h"

#include "../systems/LevelGenerationManager.h"

LevelSetup::LevelSetup()
{
    load_level_delegate = Event::EventDelegate<LevelSetup, OnLoadNewLevel>(
        this, &LevelSetup::setup_new_level);
}

void LevelSetup::on_enable()
{
    Event::EventEngine::get_instance().add_listener<OnLoadNewLevel>(
        &load_level_delegate);
}

void LevelSetup::on_disable()
{
    Event::EventEngine::get_instance().remove_listener<OnLoadNewLevel>(
        &load_level_delegate);
}

void LevelSetup::setup_new_level(const OnLoadNewLevel* event)
{
    auto level_gen_man = ECS::SystemEngine::get_instance()
                             .get_independent_system<LevelGenerationManager>();

    auto level_data =
        level_gen_man->dungeon_level_generator.get_generated_level<10, 10>();
}