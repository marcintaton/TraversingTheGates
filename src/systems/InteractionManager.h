#pragma once

#include <memory>
#include <unordered_map>

#include "../engine/GameEngine.h"
#include "../interactionLogic/IInteractive.h"

class InteractionManager :
    public ECS::System::IndependentSystem<InteractionManager>
{
  private:
    std::unordered_map<ECS::EntityTypeId, std::shared_ptr<IInteractive>>
        logic_systems;

  public:
    InteractionManager();
};