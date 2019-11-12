#pragma once

#include <array>
#include <bitset>

#include "../components/GameComponents.h"
#include "../engine/GameEngine.h"
#include "../global/GlobalData.h"
#include "LevelData.h"

struct Navmesh {
    std::array<std::bitset<Global::GlobalData::max_map_size>,
               Global::GlobalData::max_map_size>
        static_elements;
    std::array<std::bitset<Global::GlobalData::max_map_size>,
               Global::GlobalData::max_map_size>
        dynamic_elements;

    inline bool is_available(int i, int j)
    {
        return (static_elements[i][j] && dynamic_elements[i][j]);
    }

    void init_from_level_data(LevelData data);
    void move_dynamic_element(MapPosition old_position,
                              MapPosition new_position);
};
