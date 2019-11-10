#pragma once

#include "../engine/GameEngine.h"

#include "../entities/Tile.h"
#include "../systems/Renderer.h"

void setup_game_objects()
{
    ECS::EntityId t1_id = ECS::ECEngine::get_instance().create_entity<Tile>();
    ECS::ECEngine::get_instance().add_component<Transform>(t1_id);
    ECS::ECEngine::get_instance().add_component<MeshRenderData>(t1_id);

    ECS::EntityId t2_id = ECS::ECEngine::get_instance().create_entity<Tile>();
    ECS::ECEngine::get_instance().add_component<Transform>(t2_id);
    ECS::ECEngine::get_instance().add_component<MeshRenderData>(t2_id);

    ECS::EntityId t3_id = ECS::ECEngine::get_instance().create_entity<Tile>();
    ECS::ECEngine::get_instance().add_component<Transform>(t3_id);
    ECS::ECEngine::get_instance().add_component<MeshRenderData>(t3_id);
}

void setup_systems()
{

    ECS::SystemEngine::get_instance().create_active_system<Renderer>();
}