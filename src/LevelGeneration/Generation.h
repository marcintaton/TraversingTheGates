#pragma once

#include "../engine/GameEngine.h"
#include "../global/GlobalData.h"
#include <array>
#include <vector>

using BlueprintStructure =
    std::array<std::array<std::vector<int>, Global::GlobalData::max_map_size>,
               Global::GlobalData::max_map_size>;

using NavmeshStructure =
    std::array<std::array<std::vector<bool>, Global::GlobalData::max_map_size>,
               Global::GlobalData::max_map_size>;

using MapStructure = std::array<
    std::array<std::vector<ECS::EntityId>, Global::GlobalData::max_map_size>,
    Global::GlobalData::max_map_size>;