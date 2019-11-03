#pragma once

#include <array>
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

#include "../API.h"

#include "../entity/IEntity.h"
#include "IComponent.h"
#include "component.h"
#include "componentCluster.h"
#include "componentIterator.h"

template<class T>
bool assert_valid_component_type()
{
    return std::is_base_of<IComponent, T>::value;
}

class ComponentManager
{
  private:
    std::map<ComponentTypeId, std::vector<ComponentPtr>> components_by_types;
    std::map<EntityId, ComponentArray> components_by_entities;

  public:
    ComponentManager();
    ~ComponentManager();

    template<typename T, typename... T_args>
    ComponentPtr add_component(EntityId to_entity, T_args&&... args)
    {
        if (assert_valid_component_type<T>()) {

            if (components_by_entities[to_entity]
                                      [read_component_type_id<T>()] ==
                nullptr) {

                return do_add_component<T>(to_entity,
                                           std::forward<T_args>(args)...);
            } else {
                std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::ADD_COMPONENT "
                             "Entity already has this component"
                          << std::endl;
                return nullptr;
            }
        } else {
            std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::ADD_COMPONENT "
                         "Invalid component type"
                      << std::endl;
            return nullptr;
        }
    }

    template<typename T, typename... T_args>
    ComponentPtr do_add_component(EntityId to_entity, T_args&&... args)
    {
        ComponentPtr new_comp(new T(std::forward<T_args>(args)...));

        components_by_entities[to_entity][new_comp->get_component_type_id()] =
            new_comp;
        components_by_types[new_comp->get_component_type_id()].push_back(
            new_comp);

        return new_comp;
    }

    template<class T>
    void remove_component(EntityId from_entity)
    {
        if (assert_valid_component_type<T>()) {

            ComponentTypeId comp_type_id = read_component_type_id<T>();
            ComponentId comp_id =
                components_by_entities[from_entity][comp_type_id]
                    ->get_component_id();
            components_by_entities[from_entity][comp_type_id] = nullptr;

            auto it = std::find_if(
                components_by_types[comp_type_id].begin(),
                components_by_types[comp_type_id].end(), [&](const auto& comp) {
                    return comp->get_component_id() == comp_id;
                });
            components_by_types[comp_type_id].erase(it);

        } else {
            std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::REMOVE_COMPONENT "
                         "Invalid component type"
                      << std::endl;
        }
    }

    template<typename T>
    std::shared_ptr<T> get_component(EntityId from_entity)
    {
        std::shared_ptr<T> comp_ptr = std::dynamic_pointer_cast<T>(
            components_by_entities[from_entity][read_component_type_id<T>()]);

        if (comp_ptr == nullptr) {
            std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::GET_COMPONENT "
                         "No such Component in this entity"
                      << std::endl;
        }
        return std::dynamic_pointer_cast<T>(comp_ptr);
    }

    template<class T>
    ComponentIterator<T> get_components_of_type()
    {
        ComponentIterator<T> cp_it;
        for (auto comp : components_by_types[read_component_type_id<T>()]) {
            cp_it.components.push_back(std::dynamic_pointer_cast<T>(comp));
        }
        return cp_it;
    }

    template<class... Ts>
    ComponentMask generate_mask_from_types()
    {
        ComponentMask new_mask;
        return (new_mask.set(read_component_type_id<Ts>(), 1), ...);
        return new_mask;
    }

    template<class... Ts>
    ComponentCluster<Ts...>
    get_component_cluster(std::vector<EntityId> fitting_ids)
    {
        ComponentCluster<Ts...> cs;
        //
        return cs;
    }

    void clear_entity_trace(EntityId of_entity,
                            ComponentIdArray with_components);
};