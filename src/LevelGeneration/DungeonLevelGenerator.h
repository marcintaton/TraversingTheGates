#pragma once

#include "../engine/GameEngine.h"
#include "LevelBlueprint.h"
#include "LevelData.h"

#include "../systems/ShaderManager.h"
#include "../systems/TextureManager.h"

#include "../entities/Player.h"
#include "../entities/Tile.h"
#include "../entities/Wall.h"

// For now here

class DungeonLevelGenerator
{
  private:
    template<int W, int H>
    LevelBlueprint<W, H> generate_blueprint()
    {
        auto blueprint = LevelBlueprint<W, H>();

        blueprint.base_level = {{
            {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
            {{0, 0, 2, 2, 2, 2, 2, 0, 0, 0}},
            {{0, 0, 2, 1, 1, 1, 2, 0, 0, 0}},
            {{0, 0, 2, 1, 1, 1, 2, 2, 2, 0}},
            {{2, 2, 2, 1, 1, 1, 1, 1, 2, 0}},
            {{2, 1, 1, 1, 1, 1, 1, 1, 2, 0}},
            {{2, 2, 2, 1, 1, 1, 1, 1, 2, 0}},
            {{0, 0, 2, 1, 1, 1, 1, 1, 2, 0}},
            {{0, 0, 2, 2, 2, 2, 2, 2, 2, 0}},
            {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
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
    template<int W, int H>
    LevelData<W, H> get_generated_level()
    {
        auto blueprint = generate_blueprint<W, H>();
        auto data = LevelData<W, H>();

        GLuint textures[4];

        textures[1] = ECS::SystemEngine::get_instance()
                          .get_independent_system<TextureManager>()
                          ->get_texture(TextureType::GROUND);

        textures[2] = ECS::SystemEngine::get_instance()
                          .get_independent_system<TextureManager>()
                          ->get_texture(TextureType::WALL);

        textures[3] = ECS::SystemEngine::get_instance()
                          .get_independent_system<TextureManager>()
                          ->get_texture(TextureType::PLAYER);

        Shader core_sh = ECS::SystemEngine::get_instance()
                             .get_independent_system<ShaderManager>()
                             ->core_shader;

        for (int i = 0; i < W; ++i) {
            for (int j = 0; j < H; ++j) {
                auto base_type = blueprint.base_level[i][j];
                data.base_level[i][j] = create_entity_for_tile(
                    i, j, base_type, core_sh, textures[base_type]);

                auto top_type = blueprint.top_level[i][j];
                data.top_level[i][j] = create_entity_for_tile(
                    i, j, top_type, core_sh, textures[top_type]);
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