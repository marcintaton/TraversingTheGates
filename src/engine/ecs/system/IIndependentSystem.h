#pragma once

#include <memory>

#include "../ECSAPI.h"

namespace ECS
{
namespace System
{

class IIndependentSystem;
using IndpdntSystemPtr = std::shared_ptr<IIndependentSystem>;

class IIndependentSystem
{
    friend class IndependentSystemManager;

  private:
    bool enabled = true;
    SystemTypeId type_id;

  public:
    IIndependentSystem(SystemTypeId id) : type_id(id) {}
    inline const SystemTypeId get_system_type_id() const { return type_id; }
    inline bool is_enabled() { return enabled; }
    virtual void on_enable() = 0;
    virtual void on_disable() = 0;
};

}; // namespace System
}; // namespace ECS