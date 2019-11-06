#pragma once

#include "../../utility/typeHelper.h"
#include "IEvent.h"

template<class T>
class Event : public IEvent
{
  public:
    static const EventTypeId EVENT_TYPE_ID;
    Event() : IEvent(EVENT_TYPE_ID) {}
};

template<class T>
const EventTypeId
    Event<T>::EVENT_TYPE_ID = utility::type_helper::get_type_id<Event<T>>();