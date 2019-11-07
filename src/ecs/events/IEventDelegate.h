#pragma once

#include <algorithm>

#include "IEvent.h"

namespace Event
{

    using EventDelegateId = std::size_t;

    class IEventDelegate
    {
      public:
        virtual inline void invoke(IEvent* event) = 0;
        virtual inline EventDelegateId get_delegate_id() const = 0;
        virtual inline EventTypeId get_event_type_id() const = 0;
        virtual bool operator==(const IEventDelegate* other) const = 0;
    };

    // get rid of all inline fuction used but never defined warnings (for now)
    inline void IEventDelegate::invoke(IEvent* event) {}

    inline EventDelegateId IEventDelegate::get_delegate_id() const { return 0; }

    inline EventTypeId IEventDelegate::get_event_type_id() const { return 0; }
}; // namespace Event
