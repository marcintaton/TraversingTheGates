#pragma once

#include <vector>

#include "../components/GameComponents.h"
#include "../engine/GameEngine.h"
#include "../entities/GameEntities.h"
#include "../events/GameEvents.h"

class PlayerMovement : public ECS::System::IndependentSystem<PlayerMovement>
{

  private:
    int max_offset_from_player = 5;
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