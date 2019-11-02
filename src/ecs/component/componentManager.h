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

#include "../ECSEngine/EntityManagerAccess.h"

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

            ECSEngine::EntityManagerAccess::get()
                ->get_entity(to_entity)
                ->add_component_info<T>(new_comp->get_component_id());

            return new_comp;
        } else {
            std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::ADD_COMPONENT::"
                         "INVALID_COMPONENT_TYPE"
                      << std::endl;
            return nullptr;
        }
    }

    template<class T>
    void remove_component(EntityId from_entity)
    {
        if (assert_valid_component_type<T>()) {

            ComponentTypeId comp_type_id = read_component_type_id<T>();
            components_by_entities[from_entity][comp_type_id] = nullptr;

            std::shared_ptr<IEntity> entity =
                ECSEngine::EntityManagerAccess::get()->get_entity(from_entity);

            ComponentId this_comp_id = entity->get_component_id<T>();

            auto it = std::find_if(
                components_by_types[comp_type_id].begin(),
                components_by_types[comp_type_id].end(), [&](const auto& comp) {
                    return comp->get_component_id() == this_comp_id;
                });
            components_by_types[comp_type_id].erase(it);

            entity->remove_component_info<T>();

        } else {
            std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::REMOVE_COMPONENT::"
                         "INVALID_COMPONENT_TYPE"
                      << std::endl;
        }
    }

    template<typename T>
    std::shared_ptr<T> get_component(EntityId from_entity)
    {
        std::shared_ptr<T> comp_ptr = std::dynamic_pointer_cast<T>(
            components_by_entities[from_entity][read_component_type_id<T>()]);

        if (comp_ptr == nullptr) {
            std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::GET_COMPONENT::"
                         "NO_SUCH_COMPONENT_IN_ENTITY"
                      << std::endl;
        }
        return std::dynamic_pointer_cast<T>(
            components_by_entities[from_entity][read_component_type_id<T>()]);
    }
};