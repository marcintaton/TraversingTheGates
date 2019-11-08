#pragma once

#include <algorithm>

namespace Utility
{
namespace Math
{
inline std::size_t get_cantor_pairing(std::size_t a, std::size_t b)
{
    return ((a + b) * (a + b + 1) + b) >> 1;
}
}; // namespace Math
}; // namespace Utility