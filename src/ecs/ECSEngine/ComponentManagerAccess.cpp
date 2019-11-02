#include "ComponentManagerAccess.h"

std::shared_ptr<ComponentManager> ECSEngine::ComponentManagerAccess::get()
{
    std::shared_ptr<ComponentManager> component_manager =
        std::shared_ptr<ComponentManager>(new ComponentManager);
    return component_manager;
}