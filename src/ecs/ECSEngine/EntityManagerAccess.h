#pragma once

#include <memory>

#include "../entity/entityManager.h"
namespace ECSEngine
{
struct EntityManagerAccess {
    static std::shared_ptr<EntityManager> get();
};
}; // namespace ECSEngine
