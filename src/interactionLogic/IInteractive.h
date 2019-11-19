#pragma once

#include "../engine/GameEngine.h"

class IInteractive
{
  public:
    virtual void OnKick(ECS::EntityId source, ECS::EntityId target) = 0;
    virtual void OnUse(ECS::EntityId source, ECS::EntityId target) = 0;
};
