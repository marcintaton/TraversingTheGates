#pragma once

#include <vector>

#include "../components/GameComponents.h"
#include "../engine/GameEngine.h"
#include "../entities/GameEntities.h"
#include "../events/GameEvents.h"
#include "../systems/GameSystems.h"

class PlayerMovement : public ECS::System::IndependentSystem<PlayerMovement>
{

  private:
    ECS::EntityId player_id;
    std::shared_ptr<Transform> player_transform;
    Event::EventDelegate<PlayerMovement, KeyPress> movement_delegate;
    std::vector<int> expected_keys;

    void subscribe();
    void unsubscribe();

  public:
    PlayerMovement();
    virtual void on_enable() override;
    virtual void on_disable() override;

    void receive_key_input(const KeyPress* event);
    void move_player(int key_code);
};