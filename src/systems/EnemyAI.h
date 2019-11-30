#pragma once

#include "../components/GameComponents.h"
#include "../engine/GameEngine.h"
#include "../entities/GameEntities.h"
#include "../events/GameEvents.h"

class EnemyAI : public ECS::System::IndependentSystem<EnemyAI>
{

  private:
    std::shared_ptr<NavigationData> player_nav_data;
    Event::EventDelegate<EnemyAI, TurnEnd> turn_end_delegate;

    void subscribe();
    void unsubscribe();

  public:
    EnemyAI();
    virtual void on_enable() override;
    virtual void on_disable() override;

    void on_turn_end(const TurnEnd* event);
    void execute_enemy_actions();
    bool is_position_in_range(MapPosition central, int range,
                              MapPosition other);
    void attack_player();
    void move_towards_player(MapPosition enemy, MapPosition player);
};