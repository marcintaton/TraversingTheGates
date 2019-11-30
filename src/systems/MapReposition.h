#pragma once

#include "../engine/GameEngine.h"
#include "../events/GameEvents.h"

class MapReposition : public ECS::System::IndependentSystem<MapReposition>
{

  private:
    Event::EventDelegate<MapReposition, ObjectMoved> obj_moved_delegate;

    void subscribe();
    void unsubscribe();

  public:
    MapReposition();
    virtual void on_enable() override;
    virtual void on_disable() override;

    void on_object_reposition(const ObjectMoved* event);
};