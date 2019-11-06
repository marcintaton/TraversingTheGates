#pragma once

#include "IComponent.h"
#include <memory>
#include <vector>

template<class T>
struct ComponentIterator {
    std::vector<std::shared_ptr<T>> components;
};