#pragma once

#include <algorithm>
#include <memory>

#include "../ECSAPI.h"

namespace ECS
{
namespace System
{
class ISystem;
using SystemPtr = std::shared_ptr<ISystem>;

class ISystem
{
    friend class SystemManager;

  private:
    std::size_t execution_priority = 0;
    SystemTypeId type_id;

  protected:
    virtual void update() = 0;

  public:
    ISystem(SystemTypeId id) : type_id(id) {}
    inline const SystemTypeId get_system_type_id() const { return type_id; }
    virtual void on_enable() = 0;
    virtual void on_disable() = 0;

    inline void set_priority(std::size_t priority)
    {
        execution_priority = priority;
    }
    inline std::size_t get_priority() { return execution_priority; }

    bool operator<(const ISystem& other) const;
};

}; // namespace System
}; // namespace ECS
