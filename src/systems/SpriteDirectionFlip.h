#pragma once

#include "../engine/GameEngine.h"
#include "../events/GameEvents.h"

class SpriteDirectionFlip :
    public ECS::System::IndependentSystem<SpriteDirectionFlip>
{
  private:
    Event::EventDelegate<SpriteDirectionFlip, ObjectMoved> flip_delegate;

    void subscribe();
    void unsubscribe();

    void flip_sprite(const ObjectMoved* event);

  public:
    SpriteDirectionFlip();
    virtual void on_enable() override;
    virtual void on_disable() override;
};
