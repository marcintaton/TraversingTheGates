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
            spdlog::error("Event::EventDispatcher::add_delegate - Deleagate "
                          "already exists among listeners.");
        }
    }

    virtual void remove_delegate(IEventDelegate* delegate) override
    {
        auto it = std::find(listeners.begin(), listeners.end(), delegate);
        if (it != listeners.end()) {
            listeners.erase(it);
        } else {
            spdlog::error("Event::EventDispatcher::remove_delegate - Deleagate "
                          "does not exist among listeners.");
        }
    }
};
}; // namespace Event