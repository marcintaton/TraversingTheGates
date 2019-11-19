#pragma once

#include <memory>
#include <unordered_map>

#include "../engine/GameEngine.h"
#include "../events/GameEvents.h"
#include "../interactionLogic/IInteractive.h"

class InteractionManager :
    public ECS::System::IndependentSystem<InteractionManager>
{
  private:
    std::unordered_map<ECS::EntityTypeId, std::shared_ptr<IInteractive>>
        logic_systems;

    Event::EventDelegate<InteractionManager, Kick> kick_delegate;
    Event::EventDelegate<InteractionManager, Use> use_delegate;

    void subscribe();
    void unsubscribe();

    void receive_kick(const Kick* event);
    void receive_use(const Use* event);

  public:
    InteractionManager();
    virtual void on_enable() override;
    virtual void on_disable() override;
};