#pragma once

#include "../../utility/Type.h"
#include "IIndependentSystem.h"

namespace ECS
{
namespace System
{
template<class T>
class IndependentSystem : public IIndependentSystem
{
  private:
    static const SystemTypeId SYSTEM_TYPE_ID;

  public:
    IndependentSystem() : IIndependentSystem(SYSTEM_TYPE_ID) {}
    virtual void on_enable() override {}
    virtual void on_disable() override {}
};

template<class T>
const SystemTypeId IndependentSystem<T>::SYSTEM_TYPE_ID =
    Utility::Type::get_type_id<IndependentSystem<T>>();
}; // namespace System
}; // namespace ECS