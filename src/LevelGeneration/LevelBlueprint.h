#pragma once

#include <array>

template<int W, int H>
struct LevelBlueprint {
    std::array<std::array<int, H>, W> base_level;
    std::array<std::array<int, H>, W> top_level;
};
