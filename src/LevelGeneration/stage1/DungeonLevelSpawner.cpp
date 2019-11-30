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

    GLuint npc_tex = ECS::SystemEngine::get_instance()
                         .get_independent_system<TextureManager>()
                         ->get_texture(TextureType::NPCS_STAGE_1);

    Shader sh = ECS::SystemEngine::get_instance()
                    .get_independent_system<ShaderManager>()
                    ->basic_sh;

    // generate entities
    for (int i = 0; i < max_map_size; ++i) {
        for (int j = 0; j < max_map_size; ++j) {

            for (auto e : blueprint.level[i][j]) {
                auto tex = e != 3 && e != 6 ? enviro_tex :
                                              (e == 3 ? player_tex : npc_tex);
                data.level[i][j].push_back(
                    create_entity_for_tile(i, j, e, sh, tex));
            }
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
        case TileTypes::SKELETON_NPC:
            return ECS::ECEngine::get_instance().create_entity<SkeletonNPC>(
                glm::vec3(i, j, 1), sh, tex);
            break;

        default:
            return 0;
            break;
    }
}