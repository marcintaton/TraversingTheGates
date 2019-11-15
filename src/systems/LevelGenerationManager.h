#pragma once

#include "../LevelGeneration/LevelBlueprint.h"
#include "../LevelGeneration/stage1/DungeonLevelGenerator.h"
#include "../LevelGeneration/stage1/DungeonLevelSpawner.h"
#include "../engine/GameEngine.h"

class LevelGenerationManager :
    public ECS::System::IndependentSystem<LevelGenerationManager>
{
  private:
    DungeonLevelGenerator dungeon_level_generator;
    DungeonLevelSpawner dungeon_level_spawner;

  public:
    LevelData generate_dungeon_level();
};