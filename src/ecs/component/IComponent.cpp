#include "IComponent.h"

ECS::Component::IComponent::IComponent()
{
    component_id = get_new_component_id();
}
