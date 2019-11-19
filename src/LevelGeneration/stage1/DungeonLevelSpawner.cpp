#include "DungeonLevelSpawner.h"

#include "../../systems/GameSystems.h"
#include "../TileTypes.h"

LevelData DungeonLevelSpawner::get_generated_level(LevelBlueprint blueprint)
{
    auto max_map_size = Global::GlobalData::get_instance().max_map_size;
    auto data = LevelData();

    // prepare data for construtors
    GLuint enviro_tex = ECS::SystemEngine::get_instance()
                            .get_independent_system<TextureManager>()
                            ->get_texture(TextureType::ENVIRO_STAGE_1);

    GLuint player_tex = ECS::SystemEngine::get_instance()
                            .get_independent_system<TextureManager>()
                            ->get_texture(TextureType::PLAYER);

    Shader sh = ECS::SystemEngine::get_instance()
                    .get_independent_system<ShaderManager>()
                    ->basic_sh;

    // generate entities
    for (int i = 0; i < max_map_size; ++i) {
        for (int j = 0; j < max_map_size; ++j) {
            // another loop here with switch inside when we rework map into
            // nesting vectors as layers
            auto base_type = blueprint.base_level[i][j];
            data.base_level[i][j] =
                create_entity_for_tile(i, j, base_type, sh, enviro_tex);

            auto top_type = blueprint.top_level[i][j];
            GLuint top_tex = top_type == 3 ? player_tex : enviro_tex;
            data.top_level[i][j] =
                create_entity_for_tile(i, j, top_type, sh, top_tex);
        }
    }

    return data;
}

ECS::EntityId DungeonLevelSpawner::create_entity_for_tile(int i, int j,
                                                          int type, Shader sh,
                                                          GLuint tex)
{
    switch (type) {
        case TileTypes::EMPTY:
            return 0;
            break;
        case TileTypes::FLOOR_TILE:
            return ECS::ECEngine::get_instance().create_entity<Tile>(
                glm::vec3(i, j, 0), sh, tex);
            break;
        case TileTypes::WALL:
            return ECS::ECEngine::get_instance().create_entity<Wall>(
                glm::vec3(i, j, 0), sh, tex);
            break;
        case TileTypes::PLAYER:
            return ECS::ECEngine::get_instance().create_entity<Player>(
                glm::vec3(i, j, 5), sh, tex);
            break;
        case TileTypes::DOOR_H:
            return ECS::ECEngine::get_instance().create_entity<Door>(
                glm::vec3(i, j, 1), sh, tex, false);
            break;
        case TileTypes::DOOR_V:
            return ECS::ECEngine::get_instance().create_entity<Door>(
                glm::vec3(i, j, 1), sh, tex, true);
            break;

        default:
            return 0;
            break;
    }
}