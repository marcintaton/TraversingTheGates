#pragma once

#include <map>
#include <memory>
#include <type_traits>
#include <vector>

#include "IComponent.h"
#include "component.h"

template<class T>
bool assert_valid_component_type()
{
    return std::is_base_of<IComponent, T>::value;
}

class ComponentManager
{
  private:
    std::map<ComponentTypeId, std::vector<std::shared_ptr<IComponent>>>
        components_by_types;

  public:
    ComponentManager();
    ~ComponentManager();
};