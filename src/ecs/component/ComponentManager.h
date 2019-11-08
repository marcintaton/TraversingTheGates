#pragma once

#include <array>
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

#include "../ECSAPI.h"

#include "../entity/IEntity.h"
#include "../utility/AssertType.h"
#include "Component.h"
#include "ComponentCluster.h"
#include "IComponent.h"

namespace ECS
{
namespace Component
{

class ComponentManager
{
  private:
    std::map<ComponentTypeId, std::vector<ComponentPtr>> components_by_types;
    std::map<EntityId, ComponentArray> components_by_entities;

    template<class T, typename... T_args>
    ComponentPtr do_add_component(EntityId to_entity, T_args&&... args)
    {
        ComponentPtr new_comp =
            std::make_shared<T>(std::forward<T_args>(args)...);

        components_by_entities[to_entity][new_comp->get_component_type_id()] =
            new_comp;
        components_by_types[new_comp->get_component_type_id()].push_back(
            new_comp);

        return new_comp;
    }

  public:
    ComponentManager() {}
    ~ComponentManager();

    template<class T, typename... T_args>
    ComponentPtr add_component(EntityId to_entity, T_args&&... args)
    {
        if (ECS::AssertType::assert_valid_component_type<T>()) {

            if (components_by_entities
                    [to_entity][ECS::IdHelper::read_component_type_id<T>()] ==
                nullptr) {

                return do_add_component<T>(to_entity,
                                           std::forward<T_args>(args)...);
            } else {
                std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::ADD_"
                             "COMPONENT "
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

    template<class T>
    void remove_component(EntityId from_entity)
    {
        if (ECS::AssertType::assert_valid_component_type<T>()) {

            ComponentTypeId comp_type_id =
                ECS::IdHelper::read_component_type_id<T>();
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
            std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::REMOVE_"
                         "COMPONENT "
                         "Invalid component type"
                      << std::endl;
        }
    }

    template<class T>
    std::shared_ptr<T> get_component(EntityId from_entity)
    {
        std::shared_ptr<T> comp_ptr = std::dynamic_pointer_cast<T>(
            components_by_entities[from_entity]
                                  [ECS::IdHelper::read_component_type_id<T>()]);

        if (comp_ptr == nullptr) {
            std::cout << "ECS::COMPONENT::COMPONENT_MANAGER::GET_COMPONENT "
                         "No such Component in this entity"
                      << std::endl;
        }
        return std::dynamic_pointer_cast<T>(comp_ptr);
    }

    template<class T>
    ECSSContainer<T> get_components_of_type()
    {
        ECSSContainer<T> cp_it;
        for (auto comp :
             components_by_types[ECS::IdHelper::read_component_type_id<T>()]) {
            cp_it.push_back(std::dynamic_pointer_cast<T>(comp));
        }
        return cp_it;
    }

    template<class... Ts>
    ComponentMask generate_mask_from_types()
    {
        ComponentMask new_mask;
        return (new_mask.set(ECS::IdHelper::read_component_type_id<Ts>(), 1),
                ...);
    }

    template<class... Ts>
    ComponentCluster<Ts...>
    get_component_cluster(std::vector<EntityId> fitting_entities)
    {
        ComponentCluster<Ts...> cluster;
        for (auto entity_id : fitting_entities) {
            (cluster.add_to_cluster(
                 entity_id,
                 std::dynamic_pointer_cast<Ts>(
                     components_by_entities
                         [entity_id]
                         [ECS::IdHelper::read_component_type_id<Ts>()])),
             ...);
        }
        return cluster;
    }

    void clear_entity_trace(EntityId of_entity,
                            ComponentIdArray with_components);
};
}; // namespace Component
}; // namespace ECS