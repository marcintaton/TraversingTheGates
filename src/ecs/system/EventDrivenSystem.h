#pragma once

#include "IEventDrivenSystem.h"

template<class T>
class EventDrivenSystem : public IEventDrivenSystem
{
  public:
    static const SystemTypeId SYSTEM_TYPE_ID;
    EventDrivenSystem() : IEventDrivenSystem(SYSTEM_TYPE_ID) {}
    virtual void on_enable() override {}
    virtual void on_disable() override {}
};
template<class T>
const SystemTypeId EventDrivenSystem<T>::SYSTEM_TYPE_ID =
    utility::type::get_type_id<EventDrivenSystem<T>>();