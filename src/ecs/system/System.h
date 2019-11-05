#pragma once

#include "../../utility/typeHelper.h"
#include "ISystem.h"

template<class T>
class System : public ISystem
{
  protected:
    virtual void update() {}

  public:
    static const SystemTypeId SYSTEM_TYPE_ID;
    System() : ISystem(SYSTEM_TYPE_ID) {}
    virtual void on_enable() override {}
    virtual void on_disable() override {}
};

template<class T>
const SystemTypeId
    System<T>::SYSTEM_TYPE_ID = utility::type_helper::get_type_id<System<T>>();