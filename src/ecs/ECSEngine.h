#pragma once

#include <memory>

#include "component/componentManager.h"
#include "entity/entityManager.h"
#include "events/eventManager.h"

class EventManager;
class EntityManager;
class ComponentManager;

class ECSEngine
{
  public:
    // static std::shared_ptr<EventManager> event_manager;
    // static std::shared_ptr<EntityManager> entity_manager;
    // static std::shared_ptr<ComponentManager> component_manager;

    static std::shared_ptr<EventManager> event_manager();
    static std::shared_ptr<EntityManager> entity_manager();
    static std::shared_ptr<ComponentManager> component_manager();
};
