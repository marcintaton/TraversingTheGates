#include "componentManager.h"

ComponentManager::ComponentManager() {}

ComponentManager::~ComponentManager()
{
    components_by_types.clear();
}