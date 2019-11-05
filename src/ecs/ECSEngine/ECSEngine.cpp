#include "ECSEngine.h"

ECS::ECSEngine::ECSEngine()
{
    component_manager = std::make_unique<ComponentManager>();
    entity_manager = std::make_unique<EntityManager>();
    system_manager = std::make_unique<SystemManager>();
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