#include "ECEngine.h"

ECS::ECEngine::ECEngine()
{
    component_manager = std::make_unique<ECS::Component::ComponentManager>();
    entity_manager = std::make_unique<ECS::Entity::EntityManager>();
}

void ECS::ECEngine::remove_entity(EntityId by_id)
{
    if (entity_manager->does_entity_exist(by_id)) {
        component_manager->clear_entity_trace(
            by_id, entity_manager->get_component_ids(by_id));
        entity_manager->remove_entity(by_id);
    } else {
        spdlog::error("ECS::ECEngine::remove_entity - No entity by this Id");
    }
}

ECS::Entity::EntityPtr ECS::ECEngine::get_entity(EntityId by_id)
{
    return entity_manager->get_entity(by_id);
}