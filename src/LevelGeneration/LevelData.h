#pragma once

#include "../engine/GameEngine.h"
#include "../global/GlobalData.h"
#include "MapPosition.h"
#include <array>

struct LevelData {
    std::array<std::array<ECS::EntityId, Global::GlobalData::max_map_size>,
               Global::GlobalData::max_map_size>
        base_level;
    std::array<std::array<ECS::EntityId, Global::GlobalData::max_map_size>,
               Global::GlobalData::max_map_size>
        top_level;

    MapPosition find_element_position(ECS::EntityId id);
    void move_element(ECS::EntityId id, MapPosition new_position);
    void move_element(MapPosition old_position, MapPosition new_position);
};
