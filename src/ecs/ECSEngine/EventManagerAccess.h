#pragma once

#include <memory>

#include "../events/eventManager.h"

namespace ECSEngine
{
struct EventManagerAccess {
    static std::shared_ptr<EventManager> get();
};
}; // namespace ECSEngine