#pragma once

#include <list>

#include "../utility/Logging.h"
#include "IEventDispatcher.h"

namespace Event
{

template<class T>
class EventDispatcher : public IEventDispatcher
{
  private:
    std::list<IEventDelegate*> listeners;

  public:
    virtual void dispatch(IEvent* event) override
    {
        for (auto listener : listeners) {
            listener->invoke(event);
        }
    }

    virtual void add_delegate(IEventDelegate* delegate) override
    {
        if (std::find(listeners.begin(), listeners.end(), delegate) ==
            listeners.end()) {

            listeners.push_back(delegate);
        } else {
            spdlog::warn("Event::EventDispatcher::add_delegate - Deleagate "
                         "already exists among listeners. Aborting.");
        }
    }

    virtual void remove_delegate(IEventDelegate* delegate) override
    {
        listeners.erase(
            std::find(listeners.begin(), listeners.end(), delegate));
    }
};
}; // namespace Event