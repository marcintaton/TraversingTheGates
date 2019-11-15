#pragma once

#include <vector>

#include "../components/GameComponents.h"
#include "../engine/GameEngine.h"
#include "../entities/GameEntities.h"
#include "../events/GameEvents.h"
#include "../systems/GameSystems.h"

class PlayerKick : public ECS::System::IndependentSystem<PlayerKick>
{
  private:
    ECS::EntityId player_id;
    Event::EventDelegate<PlayerKick, KeyPress> kick_delegate;
    bool is_in_kick_state = false;
    std::vector<int> direction_keys;

    void subscribe();
    void unsubscribe();

  public:
    PlayerKick();
    virtual void on_enable() override;
    virtual void on_disable() override;

    void kick(const KeyPress* event);
};
