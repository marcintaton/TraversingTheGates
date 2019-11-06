#pragma once

#include "IEntity.h"
#include <memory>
#include <vector>

namespace ECS
{
    namespace Entity
    {

        template<class T>
        struct EntityIterator {
            std::vector<EntityPtr> entities;
        };
    }; // namespace Entity
};     // namespace ECS
