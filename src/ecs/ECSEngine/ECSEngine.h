#pragma once

#include <memory>

#include "../component/componentManager.h"
#include "../entity/entityManager.h"
#include "../events/eventManager.h"

namespace ECS
{

class ECSEngine
{
    // Singleton
  public:
    static ECSEngine& get_instance()
    {
        static ECSEngine instance;
        return instance;
    }

  private:
    ECSEngine();
    ECSEngine(ECSEngine const&) = delete;
    void operator=(ECSEngine const&) = delete;

    //

  private:
    std::unique_ptr<ComponentManager> component_manager;
    std::unique_ptr<EntityManager> entity_manager;
    std::unique_ptr<EventManager> event_manager;

  public:
    template<class T, typename... T_args>
    EntityId create_entity(T_args&&... args)
    {
        return entity_manager->create_entity<T>(std::forward<T_args>(args)...);
    }

    template<class T>
    EntityIterator<T> get_entities_of_type()
    {
        return entity_manager->get_entities_of_type<T>();
    }

    template<class T>
    ComponentIterator<T> get_components_of_type()
    {
        return component_manager->get_components_of_type<T>();
    }

    template<typename T, typename... T_args>
    std::shared_ptr<T> add_component(EntityId to_entity, T_args&&... args)
    {
        ComponentPtr new_comp = component_manager->add_component<T>(
            to_entity, std::forward<T_args>(args)...);
        entity_manager->get_entity(to_entity)->add_component_info<T>(
            new_comp->get_component_id());

        return std::dynamic_pointer_cast<T>(new_comp);
    }

    template<class T>
    void remove_component(EntityId from_entity)
    {
        component_manager->remove_component<T>(from_entity);
        entity_manager->get_entity(from_entity)->remove_component_info<T>();
    }

    template<class T>
    std::shared_ptr<T> get_component(EntityId from_entity)
    {
        return component_manager->get_component<T>(from_entity);
    }

    void remove_entity(EntityId by_id);
    EntityPtr get_entity(EntityId by_id);
};
} // namespace ECS