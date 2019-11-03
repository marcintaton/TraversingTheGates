#include "componentManager.h"

ComponentManager::ComponentManager() {}

ComponentManager::~ComponentManager()
{
    components_by_types.clear();
    components_by_entities.clear();
}

void ComponentManager::remove_components_of_entity(EntityPtr entity) {}