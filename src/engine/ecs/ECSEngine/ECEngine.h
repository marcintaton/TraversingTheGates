#pragma once

#include <memory>

#include "../component/ComponentManager.h"
#include "../entity/EntityManager.h"
#include "../system/SystemManager.h"

namespace ECS
{
class ECEngine
{
    // Singleton
  public:
    static ECEngine& get_instance()
    {
        static ECEngine instance;
        return instance;
    }

  private:
    ECEngine();
    ECEngine(ECEngine const&) = delete;
    void operator=(ECEngine const&) = delete;

    //

  private:
    std::unique_ptr<Component::ComponentManager> component_manager;
    std::unique_ptr<Entity::EntityManager> entity_manager;

  public:
    template<class T, typename... T_args>
    EntityId create_entity(T_args&&... args)
    {
        return entity_manager->create_entity<T>(std::forward<T_args>(args)...);
    }

    template<class T>
    ECSSContainer<T> get_entities_of_type()
    {
        return entity_manager->get_entities_of_type<T>();
    }

    template<class T>
    ECSSContainer<T> get_components_of_type()
    {
        return component_manager->get_components_of_type<T>();
    }

    template<typename T, typename... T_args>
    std::shared_ptr<T> add_component(EntityId to_entity, T_args&&... args)
    {
        if (entity_manager->does_entity_exist(to_entity) &&
            !entity_manager->get_entity(to_entity)->has_component<T>()) {
            Component::ComponentPtr new_comp =
                component_manager->add_component<T>(
                    to_entity, std::forward<T_args>(args)...);
            entity_manager->get_entity(to_entity)->add_component_info<T>(
                new_comp->get_component_id());

            return std::dynamic_pointer_cast<T>(new_comp);
        } else if (!entity_manager->does_entity_exist(to_entity)) {
            spdlog::error("ECS::ECEngine::add_component - No entity "
                          "with this ID");
            return nullptr;
        } else {
            spdlog::error("ECS::ECEngine::add_component - Entity already has "
                          "this component");
            return nullptr;
        }
    }

    template<class T>
    void remove_component(EntityId from_entity)
    {
        if (entity_manager->does_entity_exist(from_entity) &&
            entity_manager->get_entity(from_entity)->has_component<T>()) {

            component_manager->remove_component<T>(from_entity);
            entity_manager->get_entity(from_entity)->remove_component_info<T>();
        } else if (!entity_manager->does_entity_exist(from_entity)) {
            spdlog::error("ECS::ECEngine::remove_component - No entity "
                          "with this ID");
        } else if (!entity_manager->get_entity(from_entity)
                        ->has_component<T>()) {
            spdlog::error("ECS::ECEngine::remove_component - No such component "
                          "in this entity");
        }
    }

    template<class T>
    std::shared_ptr<T> get_component(EntityId from_entity)
    {
        return component_manager->get_component<T>(from_entity);
    }

    template<class... Ts>
    Component::ComponentCluster<Ts...> get_component_cluster()
    {
        auto mask = component_manager->generate_mask_from_types<Ts...>();
        auto fitting_entities = entity_manager->get_eintity_ids_by_mask(mask);
        return component_manager->get_component_cluster<Ts...>(
            fitting_entities);
    }

    void remove_entity(EntityId by_id);
    Entity::EntityPtr get_entity(EntityId by_id);
};
} // namespace ECS