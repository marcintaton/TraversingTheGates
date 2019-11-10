#pragma once

#include "../engine/GameEngine.h"

#include "../components/CameraData.h"
#include "../components/MeshRenderData.h"
#include "../components/Transform.h"

#include "../entities/Camera.h"
#include "../entities/Tile.h"

#include "../systems/Renderer.h"

#include "../shaders/Shader.h"
#include "TextureLoader.h"

void setup_game_objects()
{
    // load textures
    GLuint texture;
    load_texture("../../assets/textures/tile.png", texture);

    // setup some tiles
    ECS::EntityId t1_id = ECS::ECEngine::get_instance().create_entity<Tile>();
    ECS::ECEngine::get_instance().add_component<Transform>(t1_id);
    ECS::ECEngine::get_instance().add_component<MeshRenderData>(t1_id);

    ECS::EntityId t2_id = ECS::ECEngine::get_instance().create_entity<Tile>();
    ECS::ECEngine::get_instance().add_component<Transform>(t2_id);
    ECS::ECEngine::get_instance().add_component<MeshRenderData>(t2_id);

    ECS::EntityId t3_id = ECS::ECEngine::get_instance().create_entity<Tile>();
    ECS::ECEngine::get_instance().add_component<Transform>(t3_id);
    ECS::ECEngine::get_instance().add_component<MeshRenderData>(t3_id);

    // setup camera
    ECS::EntityId c_id = ECS::ECEngine::get_instance().create_entity<Camera>();
    ECS::ECEngine::get_instance().add_component<Transform>(c_id);
    ECS::ECEngine::get_instance().add_component<CameraData>(c_id);
}

void setup_systems()
{

    ECS::SystemEngine::get_instance().create_active_system<Renderer>();
}