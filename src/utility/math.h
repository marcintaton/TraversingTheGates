#pragma once

#include <algorithm>

namespace utility
{
namespace math
{
inline std::size_t get_cantor_pairing(std::size_t a, std::size_t b)
{
    return ((a + b) * (a + b + 1) + b) >> 1;
}
}; // namespace math
}; // namespace utility