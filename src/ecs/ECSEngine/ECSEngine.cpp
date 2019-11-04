#include "ECSEngine.h"

ECS::ECSEngine::ECSEngine()
{
    component_manager = std::unique_ptr<ComponentManager>(new ComponentManager);
    entity_manager = std::unique_ptr<EntityManager>(new EntityManager);
    // event_manager = std::unique_ptr<EventManager>(new EventManager);
}

void ECS::ECSEngine::remove_entity(EntityId by_id)
{
    component_manager->clear_entity_trace(
        by_id, entity_manager->get_component_ids(by_id));
    entity_manager->remove_entity(by_id);
}

EntityPtr ECS::ECSEngine::get_entity(EntityId by_id)
{
    return entity_manager->get_entity(by_id);
}