#pragma once

#include <algorithm>

namespace Utility
{
namespace Type
{

template<typename T>
inline std::size_t get_type_id()
{
    return typeid(T).hash_code();
}

template<typename T>
inline std::string get_type_name()
{
    return typeid(T).name();
}

} // namespace Type
} // namespace Utility