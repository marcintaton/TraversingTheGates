#pragma once

#include "../components/GameComponents.h"
#include "../engine/GameEngine.h"
#include "../entities/GameEntities.h"
#include "../events/GameEvents.h"

class CameraMovement : public ECS::System::IndependentSystem<CameraMovement>
{
  private:
    int max_offset_from_player = 2;
    std::shared_ptr<Transform> t_player;
    std::shared_ptr<Transform> t_camera;
    Event::EventDelegate<CameraMovement, PlayerMoved> movement_delegate;

    void subscribe();
    void unsubscribe();
    void try_cache_transforms();

  public:
    CameraMovement();
    virtual void on_enable() override;
    virtual void on_disable() override;

    void move_camera(const PlayerMoved* event);
    void center_on_player();
};
