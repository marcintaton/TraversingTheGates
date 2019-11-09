#pragma once

#include <type_traits>

#include "../ecs/component/IComponent.h"
#include "../ecs/entity/IEntity.h"

namespace ECS
{
namespace AssertType
{

template<class T>
inline bool assert_valid_entity_type()
{
    return std::is_base_of<Entity::IEntity, T>::value;
}

template<class T>
inline bool assert_valid_component_type()
{
    return std::is_base_of<Component::IComponent, T>::value;
}

}; // namespace AssertType
}; // namespace ECS