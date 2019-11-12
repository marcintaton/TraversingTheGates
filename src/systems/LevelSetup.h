#pragma once

#include "../engine/GameEngine.h"
#include "../events/GameEvents.h"

class LevelSetup : public ECS::System::IndependentSystem<LevelSetup>
{

  private:
    Event::EventDelegate<LevelSetup, LoadNewLevel> load_level_delegate;

    void subscribe();
    void unsubscribe();

  public:
    LevelSetup();
    virtual void on_enable() override;
    virtual void on_disable() override;

    void setup_new_level(const LoadNewLevel* event);
};