#include "LevelGenerationManager.h"

LevelData LevelGenerationManager::generate_dungeon_level()
{
    LevelBlueprint blueprint =
        dungeon_level_generator.generate_procedural_blueprint();
    return dungeon_level_spawner.get_generated_level(blueprint);
}