#pragma once

#include <array>
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

#include "../entity/IEntity.h"
#include "../entity/entityManager.h"
#include "IComponent.h"
#include "component.h"

#include "../ECSEngine.h"

using ComponentArray = std::array<std::shared_ptr<IComponent>, max_components>;

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
    std::map<EntityId, ComponentArray> components_by_entities;

  public:
    ComponentManager();
    ~ComponentManager();

    template<typename T, typename... T_args>
    std::shared_ptr<IComponent> add_component(EntityId to_entity,
                                              T_args&&... args)
    {
        if (assert_valid_component_type<T>()) {

            std::shared_ptr<IComponent> new_comp(
                new T(std::forward<T_args>(args)...));

            components_by_entities[to_entity]
                                  [new_comp->get_component_type_id()] =
                                      new_comp;
            components_by_types[new_comp->get_component_type_id()].push_back(
                new_comp);

            return new_comp;
        } else {
            std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::ADD_COMPONENT::"
                         "INVALID_COMPONENT_TYPE"
                      << std::endl;
            return nullptr;
        }
    }

    void test() {}
};