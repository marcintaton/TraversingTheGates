#pragma once

#include "../global/GlobalData.h"
#include <array>

struct LevelBlueprint {
    std::array<std::array<int, Global::GlobalData::max_map_size>,
               Global::GlobalData::max_map_size>
        base_level;
    std::array<std::array<int, Global::GlobalData::max_map_size>,
               Global::GlobalData::max_map_size>
        top_level;
};
