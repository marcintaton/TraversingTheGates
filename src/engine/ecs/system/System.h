#pragma once

#include "../../utility/Type.h"
#include "ISystem.h"

namespace ECS
{
namespace System
{
template<class T>
class System : public ISystem
{
  private:
    static const SystemTypeId SYSTEM_TYPE_ID;

  protected:
    virtual void update() {}

  public:
    System() : ISystem(SYSTEM_TYPE_ID) {}
    virtual void on_enable() override {}
    virtual void on_disable() override {}
};

template<class T>
const SystemTypeId
    System<T>::SYSTEM_TYPE_ID = Utility::Type::get_type_id<System<T>>();
}; // namespace System
}; // namespace ECS
