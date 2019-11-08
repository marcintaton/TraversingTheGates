#pragma once

#include <algorithm>

#include "EventAPI.h"

namespace Event
{
class IEvent
{
  private:
    EventTypeId type_id;

  public:
    IEvent(EventTypeId id) : type_id(id) {}
    inline const EventTypeId get_event_type_id() const { return type_id; }
};

}; // namespace Event
