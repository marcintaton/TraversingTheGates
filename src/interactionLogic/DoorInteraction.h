#pragma once

#include "IInteractive.h"

class DoorInteraction : public IInteractive
{
  public:
    virtual void OnKick(const Kick* event) override;
    virtual void OnUse(const Use* event) override;
};
