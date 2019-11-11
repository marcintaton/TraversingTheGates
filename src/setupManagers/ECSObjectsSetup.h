#pragma once

#include "../engine/GameEngine.h"

#include "../components/CameraData.h"
#include "../components/MeshRenderData.h"
#include "../components/Transform.h"

#include "../entities/Camera.h"
#include "../entities/Tile.h"

#include "../systems/Renderer.h"

#include "../meshes/Quad.h"
#include "../shaders/Shader.h"
#include "TextureLoader.h"

void setup_game_objects()
{
    // load textures
    GLuint texture;
    load_texture("assets/textures/player.png", texture);

    Shader core("assets/shaders/core.vs", "assets/shaders/core.fs");

    // setup some tiles
    ECS::EntityId t1_id = ECS::ECEngine::get_instance().create_entity<Tile>();
    ECS::ECEngine::get_instance().add_component<Transform>(
        t1_id, glm::vec3(0, 0, 0), glm::vec2(1, 1), 0.0f);
    ECS::ECEngine::get_instance().add_component<MeshRenderData>(t1_id, Quad {},
                                                                core, texture);

    ECS::EntityId t2_id = ECS::ECEngine::get_instance().create_entity<Tile>();
    ECS::ECEngine::get_instance().add_component<Transform>(
        t2_id, glm::vec3(0, 1, 0), glm::vec2(1, 1), 0.0f);
    ECS::ECEngine::get_instance().add_component<MeshRenderData>(t2_id, Quad {},
                                                                core, texture);

    ECS::EntityId t3_id = ECS::ECEngine::get_instance().create_entity<Tile>();
    ECS::ECEngine::get_instance().add_component<Transform>(
        t3_id, glm::vec3(1, 0, 0), glm::vec2(1, 1), 0.0f);
    ECS::ECEngine::get_instance().add_component<MeshRenderData>(t3_id, Quad {},
                                                                core, texture);

    // setup camera
    ECS::EntityId c_id = ECS::ECEngine::get_instance().create_entity<Camera>();
    ECS::ECEngine::get_instance().add_component<Transform>(c_id);
    ECS::ECEngine::get_instance().add_component<CameraData>(c_id);
}

void setup_systems()
{

    ECS::SystemEngine::get_instance().create_active_system<Renderer>();
}