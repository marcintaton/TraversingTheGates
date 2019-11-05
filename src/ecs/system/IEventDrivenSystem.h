#pragma once

#include "ISystem.h"

class IEventDrivenSystem : public ISystem
{
  public:
    IEventDrivenSystem(SystemTypeId TYPE_ID) : ISystem(TYPE_ID) {}
    virtual void on_enable() override {}
    virtual void on_disable() override {}
};
