#pragma once

#include "IInteractive.h"

class TileInteraction : public IInteractive
{
  public:
    virtual void OnKick(ECS::EntityId source, ECS::EntityId target) override;
    virtual void OnUse(ECS::EntityId source, ECS::EntityId target) override;
};
