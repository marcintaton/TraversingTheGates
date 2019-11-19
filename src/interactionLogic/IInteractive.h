#pragma once

#include "../engine/GameEngine.h"
#include "../events/GameEvents.h"

class IInteractive
{
  public:
    virtual void OnKick(const Kick* event) = 0;
    virtual void OnUse(const Use* event) = 0;
};
