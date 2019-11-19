#pragma once

#include "../components/GameComponents.h"
#include "IInteractive.h"

class DoorInteraction : public IInteractive
{
  private:
    void open_door(ECS::EntityId door_id, std::shared_ptr<DoorData> door_data);
    void close_door(ECS::EntityId door_id, std::shared_ptr<DoorData> door_data);

  public:
    virtual void OnKick(const Kick* event) override;
    virtual void OnUse(const Use* event) override;
};
