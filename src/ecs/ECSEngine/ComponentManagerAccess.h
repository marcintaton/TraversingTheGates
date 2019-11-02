#pragma once

#include <memory>

#include "../component/componentManager.h"

namespace ECSEngine
{
struct ComponentManagerAccess {
    static std::shared_ptr<ComponentManager> get();
};
}; // namespace ECSEngine
