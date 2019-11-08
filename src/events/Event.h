#pragma once

#include "../utility/Type.h"
#include "IEvent.h"
namespace Event
{

template<class T>
class Event : public IEvent
{
  public:
    static const EventTypeId EVENT_TYPE_ID;
    Event() : IEvent(EVENT_TYPE_ID) {}
};

template<class T>
const EventTypeId
    Event<T>::EVENT_TYPE_ID = Utility::Type::get_type_id<Event<T>>();
}; // namespace Event