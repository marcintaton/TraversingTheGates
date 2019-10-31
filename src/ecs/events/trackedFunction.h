#pragma once
#include <algorithm>

template<typename... T_args>
struct TrackedFunction {
    size_t tracking_id;
    std::function<void(T_args...)> function;
};