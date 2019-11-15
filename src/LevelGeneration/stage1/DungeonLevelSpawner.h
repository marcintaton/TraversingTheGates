#pragma once

#include "../../engine/GameEngine.h"
#include "../../shaders/Shader.h"
#include "../LevelBlueprint.h"
#include "../LevelData.h"

class DungeonLevelSpawner
{
  private:
    ECS::EntityId create_entity_for_tile(int i, int j, int type, Shader sh,
                                         GLuint tex);

  public:
    LevelData get_generated_level(LevelBlueprint blueprint);
};
