#pragma once

#include "IComponent.h"
#include <memory>
#include <vector>

namespace ECS
{
    namespace Component
    {
        template<class T>
        struct ComponentIterator {
            std::vector<std::shared_ptr<T>> components;
        };
    }; // namespace Component
};     // namespace ECS