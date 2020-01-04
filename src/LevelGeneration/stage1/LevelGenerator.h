#pragma once

#include "../../engine/GameEngine.h"
#include "../../global/GlobalData.h"
#include "../LevelBlueprint.h"
#include "../LevelData.h"

// ????
#include "../../entities/GameEntities.h"

// For now here

class LevelGenerator
{
  public:
    LevelBlueprint generate_blueprint();
    LevelBlueprint generate_full_size();
    // LevelData get_generated_level();
    // ECS::EntityId create_entity_for_tile(int i, int j, int type, Shader sh,
    //  GLuint tex);
};