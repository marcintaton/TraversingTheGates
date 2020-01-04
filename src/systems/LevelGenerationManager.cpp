#include "LevelGenerationManager.h"

LevelData LevelGenerationManager::generate_dungeon_level()
{
    LevelBlueprint blueprint = dungeon_level_generator.generate_full_size();
    return dungeon_level_spawner.get_generated_level(blueprint);
}