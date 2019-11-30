#pragma once

#include <stdlib.h>
#include <vector>

namespace Random
{

template<typename T>
struct WeightedRandOption {
    T option;
    int weight;
};

inline int rand_range(int min, int max)
{
    if (min == max) {
        return min;
    }
    return rand() % (max - min) + min;
}

template<typename T>
T weighted_rand(std::vector<WeightedRandOption<T>> options)
{
    int weight_sum = 0;
    for (auto o : options) {
        weight_sum += o.weight;
    }

    int choice = rand_range(0, weight_sum);

    int weight_incrementing_sum = 0;
    for (auto o : options) {
        weight_incrementing_sum += o.weight;
        if (choice < weight_incrementing_sum) {
            return o.option;
        }
    }

    return options.back().option;
}
} // namespace Random