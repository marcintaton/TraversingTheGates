#include "ECSEngine.h"

ECS::ECSEngine::ECSEngine()
{
    component_manager = std::shared_ptr<ComponentManager>(new ComponentManager);
    entity_manager = std::shared_ptr<EntityManager>(new EntityManager);
    event_manager = std::shared_ptr<EventManager>(new EventManager);
}

ECS::ECSEngine::~ECSEngine() {}

void ECS::ECSEngine::remove_entity(EntityId by_id)
{
    //
    entity_manager->remove_entity(by_id);
}

EntityPtr ECS::ECSEngine::get_entity(EntityId by_id)
{
    return entity_manager->get_entity(by_id);
}