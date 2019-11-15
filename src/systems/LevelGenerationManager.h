#pragma once

#include "../LevelGeneration/DungeonLevelGenerator.h"
#include "../engine/GameEngine.h"

class DungeonLevelGenerator;

class LevelGenerationManager :
    public ECS::System::IndependentSystem<LevelGenerationManager>
{
  public:
    DungeonLevelGenerator dungeon_level_generator;
};