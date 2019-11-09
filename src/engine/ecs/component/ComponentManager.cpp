#include "ComponentManager.h"

ECS::Component::ComponentManager::~ComponentManager()
{
    components_by_types.clear();
    components_by_entities.clear();
}

void ECS::Component::ComponentManager::clear_entity_trace(
    EntityId of_entity, ComponentIdArray with_components)
{
    for (int i = 0; i < max_components; ++i) {
        if (with_components[i] != 0) {
            components_by_types[i].erase(std::find_if(
                components_by_types[i].begin(), components_by_types[i].end(),
                [=](const auto& comp) {
                    return comp->get_component_id() == with_components[i];
                }));
        }
    }

    components_by_entities.erase(of_entity);
}