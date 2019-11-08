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

} // namespace Type
} // namespace Utility