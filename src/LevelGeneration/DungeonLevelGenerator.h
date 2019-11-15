#pragma once

#include "../engine/GameEngine.h"
#include "../global/GlobalData.h"
#include "LevelBlueprint.h"
#include "LevelData.h"

// ????
#include "../systems/GameSystems.h"
#include "../systems/ShaderManager.h"
#include "../systems/TextureManager.h"

#include "../entities/GameEntities.h"

// For now here

class DungeonLevelGenerator
{
  private:
    LevelBlueprint generate_blueprint()
    {
        auto blueprint = LevelBlueprint();

        blueprint.base_level = {{
            {{2, 2, 2, 2, 2, 2, 2, 2, 0, 0}},
            {{2, 1, 1, 1, 1, 1, 1, 2, 0, 0}},
            {{2, 1, 1, 1, 1, 1, 1, 2, 2, 2}},
            {{2, 1, 1, 1, 1, 1, 1, 1, 1, 2}},
            {{2, 2, 2, 1, 1, 1, 1, 1, 1, 2}},
            {{2, 1, 1, 1, 1, 1, 1, 1, 1, 2}},
            {{2, 2, 1, 1, 1, 1, 1, 1, 1, 2}},
            {{0, 2, 1, 1, 1, 1, 1, 1, 1, 2}},
            {{0, 2, 1, 1, 1, 1, 1, 1, 2, 2}},
            {{0, 2, 2, 2, 2, 2, 2, 2, 2, 2}},
        }};

        blueprint.top_level = {{{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                {{0, 0, 0, 0, 3, 0, 0, 0, 0, 0}},
                                {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}}};

        return blueprint;
    }

  public:
    LevelData get_generated_level()
    {
        auto max_map_size = Global::GlobalData::get_instance().max_map_size;
        auto blueprint = generate_blueprint();
        auto data = LevelData();

        GLuint enviro_tex = ECS::SystemEngine::get_instance()
                                .get_independent_system<TextureManager>()
                                ->get_texture(TextureType::ENVIRO_STAGE_1);

        GLuint player_tex = ECS::SystemEngine::get_instance()
                                .get_independent_system<TextureManager>()
                                ->get_texture(TextureType::PLAYER);

        Shader sh = ECS::SystemEngine::get_instance()
                        .get_independent_system<ShaderManager>()
                        ->basic_sh;

        for (int i = 0; i < max_map_size; ++i) {
            for (int j = 0; j < max_map_size; ++j) {
                auto base_type = blueprint.base_level[i][j];
                data.base_level[i][j] =
                    create_entity_for_tile(i, j, base_type, sh, enviro_tex);
            }
        }
        for (int i = 0; i < max_map_size; ++i) {
            for (int j = 0; j < max_map_size; ++j) {
                auto top_type = blueprint.top_level[i][j];
                data.top_level[i][j] =
                    create_entity_for_tile(i, j, top_type, sh, player_tex);
            }
        }

        return data;
    }

    ECS::EntityId create_entity_for_tile(int i, int j, int type, Shader sh,
                                         GLuint tex)
    {
        if (type == 1) {
            return ECS::ECEngine::get_instance().create_entity<Tile>(
                glm::vec3(i, j, 0), sh, tex);
        } else if (type == 2) {
            return ECS::ECEngine::get_instance().create_entity<Wall>(
                glm::vec3(i, j, 0), sh, tex);
        } else if (type == 3) {
            return ECS::ECEngine::get_instance().create_entity<Player>(
                glm::vec3(i, j, 1), sh, tex);
        }

        return 0;
    }
};