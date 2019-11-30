#pragma once

#include "../engine/GameEngine.h"
#include "Generation.h"
#include "MapPosition.h"
#include <array>

struct LevelData {

    MapStructure level;

    MapPosition find_element_position(ECS::EntityId id);
    void move_element(ECS::EntityId id, MapPosition new_position);
    void move_element(MapPosition old_position, MapPosition new_position);
    ECS::EntityId find_element_id(MapPosition position);
};
