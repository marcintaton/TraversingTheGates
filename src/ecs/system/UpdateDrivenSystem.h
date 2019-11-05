#pragma once

#include "IUpdateDrivenSystem.h"

template<class T>
class UpdateDrivenSystem : public IUpdateDrivenSystem
{

  protected:
    virtual void update() = 0;

  public:
    static const SystemTypeId SYSTEM_TYPE_ID;
    UpdateDrivenSystem() : IUpdateDrivenSystem(SYSTEM_TYPE_ID) {}
    virtual void on_enable() override {}
    virtual void on_disable() override {}
};

template<class T>
const SystemTypeId UpdateDrivenSystem<T>::SYSTEM_TYPE_ID =
    utility::type_helper::get_type_id<UpdateDrivenSystem<T>>();