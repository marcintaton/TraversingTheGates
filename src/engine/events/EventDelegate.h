#pragma once

#include <functional>

#include "../utility/Type.h"
#include "IEventDelegate.h"

namespace Event
{

template<class ListenerT, class EventT>
class EventDelegate : public IEventDelegate
{
    using Callback = std::function<void(const EventT*)>;
    typedef void (ListenerT::*Function)(const EventT*);

  private:
    Callback callback;

  public:
    EventDelegate() {}
    EventDelegate(ListenerT* listener, Function&& function) :
        callback(std::bind(function, listener, std::placeholders::_1))
    {
    }

    virtual inline void invoke(IEvent* event) override
    {
        callback(reinterpret_cast<const EventT*>(event));
    }

    virtual inline EventDelegateId get_delegate_id() const override
    {
        static const EventDelegateId EVENT_DELEGATE_ID =
            Utility::Type::get_type_id<EventDelegate<ListenerT, EventT>>();
        return EVENT_DELEGATE_ID;
    }

    virtual inline EventTypeId get_event_type_id() const override
    {
        static const EventTypeId EVENT_TYPE = EventT::EVENT_TYPE_ID;
        return EVENT_TYPE;
    }

    virtual bool operator==(const IEventDelegate* other) const override
    {
        std::cout << get_delegate_id() << " " << other->get_delegate_id()
                  << std::endl;
        return get_delegate_id() == other->get_delegate_id();
    }
};
}; // namespace Event
