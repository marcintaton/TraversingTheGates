#pragma once

#include "../engine/GameEngine.h"
#include <array>

template<int W, int H>
struct LevelData {
    std::array<std::array<ECS::EntityId, H>, W> base_level;
    std::array<std::array<ECS::EntityId, H>, W> top_level;
};
