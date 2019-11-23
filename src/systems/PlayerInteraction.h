#pragma once

#include <vector>

#include "../components/GameComponents.h"
#include "../engine/GameEngine.h"
#include "../entities/GameEntities.h"
#include "../events/GameEvents.h"
#include "../systems/GameSystems.h"

class PlayerInteraction :
    public ECS::System::IndependentSystem<PlayerInteraction>
{
  private:
    ECS::EntityId player_id = 0;
    Event::EventDelegate<PlayerInteraction, KeyPress> interaction_delegate;
    std::vector<int> direction_keys;

    bool is_in_kick_state = false;
    bool is_in_use_state = false;

    void subscribe();
    void unsubscribe();

    void enter_kick_state();
    void enter_use_state();
    void resolve_keys_in_kick_state(const KeyPress* event);
    void resolve_keys_in_use_state(const KeyPress* event);

    ECS::EntityId get_interacted_entity_id(const KeyPress* event);

  public:
    PlayerInteraction();
    virtual void on_enable() override;
    virtual void on_disable() override;

    void interact(const KeyPress* event);
};
