#include "EntityManagerAccess.h"

std::shared_ptr<EntityManager> ECSEngine::EntityManagerAccess::get()
{
    static std::shared_ptr<EntityManager> entity_manager =
        std::shared_ptr<EntityManager>(new EntityManager);
    return entity_manager;
}
