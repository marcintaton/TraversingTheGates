#pragma once

#include "../LevelGeneration/LevelBlueprint.h"
#include "../LevelGeneration/stage1/DungeonLevelSpawner.h"
#include "../LevelGeneration/stage1/LevelGenerator.h"
#include "../engine/GameEngine.h"

class LevelGenerationManager :
    public ECS::System::IndependentSystem<LevelGenerationManager>
{
  private:
    LevelGenerator dungeon_level_generator;
    DungeonLevelSpawner dungeon_level_spawner;

  public:
    LevelData generate_dungeon_level();
};