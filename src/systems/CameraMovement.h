#pragma once

#include "../components/GameComponents.h"
#include "../engine/GameEngine.h"
#include "../entities/GameEntities.h"
#include "../events/GameEvents.h"

class CameraMovement : public ECS::System::IndependentSystem<CameraMovement>
{
  private:
    Event::EventDelegate<CameraMovement, PlayerMoved> movement_delegate;

    void subscribe();
    void unsubscribe();

  public:
    CameraMovement();
    virtual void on_enable() override;
    virtual void on_disable() override;

    void move_camera(const PlayerMoved* event);
};
