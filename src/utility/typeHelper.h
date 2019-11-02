#pragma once

#include <algorithm>

namespace utility
{
namespace type_helper
{

template<typename T>
std::size_t get_type_id()
{
    return typeid(T).hash_code();
}

} // namespace type_helper
} // namespace utility