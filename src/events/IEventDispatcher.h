#pragma once

#include <algorithm>

#include "IEventDelegate.h"

namespace Event
{
    class IEventDispatcher
    {
      public:
        virtual void dispatch(IEvent* event) = 0;
        virtual void add_delegate(IEventDelegate* delegate) = 0;
        virtual void remove_delegate(IEventDelegate* delegate) = 0;
    };

}; // namespace Event