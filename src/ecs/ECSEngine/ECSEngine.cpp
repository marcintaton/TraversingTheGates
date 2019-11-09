#include "ECSEngine.h"

ECS::ECSEngine::ECSEngine()
{
    component_manager = std::make_unique<ECS::Component::ComponentManager>();
    entity_manager = std::make_unique<ECS::Entity::EntityManager>();
}

void ECS::ECSEngine::remove_entity(EntityId by_id)
{
    component_manager->clear_entity_trace(
        by_id, entity_manager->get_component_ids(by_id));
    entity_manager->remove_entity(by_id);
}

ECS::Entity::EntityPtr ECS::ECSEngine::get_entity(EntityId by_id)
{
    return entity_manager->get_entity(by_id);
}