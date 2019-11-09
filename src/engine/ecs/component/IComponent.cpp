#include "IComponent.h"

ECS::Component::IComponent::IComponent()
{
    component_id = ECS::IdHelper::get_new_component_id();
}
