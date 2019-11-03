#pragma once

#include <tuple>
#include <vector>

#include "../API.h"

template<typename... Ts>
struct ComponentCluster {
    std::vector<EntityId> id_lookup;
    std::vector<std::tuple<Ts...>> cluster;
};
