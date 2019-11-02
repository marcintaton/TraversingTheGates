#include "EventManagerAccess.h"

std::shared_ptr<EventManager> ECSEngine::EventManagerAccess::get()
{
    static std::shared_ptr<EventManager> event_manager =
        std::shared_ptr<EventManager>(new EventManager);
    return event_manager;
}