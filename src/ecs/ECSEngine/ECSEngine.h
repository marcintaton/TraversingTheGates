#pragma once

#include <memory>

#include "../component/componentManager.h"
#include "../entity/entityManager.h"
#include "../events/eventManager.h"

namespace ECS
{
//

class ECSEngine
{
  private:
    std::shared_ptr<ComponentManager> component_manager;
    std::shared_ptr<EntityManager> entity_manager;
    std::shared_ptr<EventManager> event_manager;

  public:
    ECSEngine();
    ~ECSEngine();

    inline std::shared_ptr<ComponentManager> get_component_manager()
    {
        return component_manager;
    }

    inline std::shared_ptr<EntityManager> get_entity_manager()
    {
        return entity_manager;
    }

    inline std::shared_ptr<EventManager> get_event_manager()
    {
        return event_manager;
    }

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

    void remove_entity(EntityId by_id);
    EntityPtr get_entity(EntityId by_id);
};
} // namespace ECS