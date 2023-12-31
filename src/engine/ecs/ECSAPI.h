#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <memory>

namespace ECS
{

constexpr std::size_t max_components = 32;
using ComponentId = std::size_t;
using ComponentTypeId = std::size_t;
using EntityId = std::size_t;
using EntityTypeId = std::size_t;
using ComponentIdArray = std::array<std::size_t, max_components>;
using ComponentMask = std::bitset<max_components>;

template<class T>
using ECSSContainer = std::vector<std::shared_ptr<T>>;

using SystemTypeId = std::size_t;
}; // namespace ECS
