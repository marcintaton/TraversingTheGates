#include "LevelSetup.h"

#include "../components/Transform.h"
#include "../entities/Camera.h"
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

    auto level_data =
        level_gen_man->dungeon_level_generator.get_generated_level<10, 10>();

    auto player_id = ECS::ECEngine::get_instance()
                         .get_entities_of_type<Player>()[0]
                         ->get_entity_id();
    auto player_trans =
        ECS::ECEngine::get_instance().get_component<Transform>(player_id);

    auto camera_id = ECS::ECEngine::get_instance()
                         .get_entities_of_type<Camera>()[0]
                         ->get_entity_id();
    auto camera_trans =
        ECS::ECEngine::get_instance().get_component<Transform>(camera_id);

    camera_trans->position = player_trans->position;
}