#include "ECSEngine.h"

// std::shared_ptr<EventManager> ECSEngine::event_manager(new EventManager);
// std::shared_ptr<EntityManager> ECSEngine::entity_manager(new EntityManager);
// std::shared_ptr<ComponentManager>
//     ECSEngine::component_manager(new ComponentManager);

std::shared_ptr<EventManager> ECSEngine::event_manager()
{
    static std::shared_ptr<EventManager> event_manager =
        std::shared_ptr<EventManager>(new EventManager);
    return event_manager;
}

std::shared_ptr<EntityManager> ECSEngine::entity_manager()
{
    static std::shared_ptr<EntityManager> entity_manager =
        std::shared_ptr<EntityManager>(new EntityManager);
    return entity_manager;
}

std::shared_ptr<ComponentManager> ECSEngine::component_manager()
{
    std::shared_ptr<ComponentManager> component_manager =
        std::shared_ptr<ComponentManager>(new ComponentManager);
    return component_manager;
}
