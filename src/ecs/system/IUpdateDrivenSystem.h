#pragma once

#include "ISystem.h"

class IUpdateDrivenSystem : public ISystem
{
    friend class SystemManager;

  protected:
    virtual void update() = 0;

  public:
    IUpdateDrivenSystem(SystemTypeId TYPE_ID) : ISystem(TYPE_ID) {}
    virtual void on_enable() override {}
    virtual void on_disable() override {}
};
