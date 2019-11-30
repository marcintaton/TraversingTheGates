#include "EnemyAI.h"

EnemyAI::EnemyAI()
{
    turn_end_delegate =
        Event::EventDelegate<EnemyAI, TurnEnd>(this, &EnemyAI::on_turn_end);
}

void EnemyAI::subscribe()
{
    Event::EventEngine::get_instance().add_listener<TurnEnd>(
        &turn_end_delegate);
}

void EnemyAI::unsubscribe()
{
    Event::EventEngine::get_instance().remove_listener<TurnEnd>(
        &turn_end_delegate);
}

void EnemyAI::on_enable()
{
    subscribe();
}

void EnemyAI::on_disable()
{
    unsubscribe();
}

void EnemyAI::on_turn_end(const TurnEnd* event)
{
    if (player_nav_data == nullptr) {
        auto player_id = ECS::ECEngine::get_instance()
                             .get_entities_of_type<Player>()[0]
                             ->get_entity_id();
        player_nav_data =
            ECS::ECEngine::get_instance().get_component<NavigationData>(
                player_id);
    }

    execute_enemy_actions();
}

void EnemyAI::execute_enemy_actions()
{
    auto cluster = ECS::ECEngine::get_instance()
                       .get_component_cluster<NavigationData, EnemyNPCData>();

    auto player_pos = player_nav_data->current_position;

    for (int i = 0; i < cluster.cluster.size(); ++i) {
        auto enemy_nav_data = cluster.get_component<NavigationData>(i);
        auto enemy_data = cluster.get_component<EnemyNPCData>(i);
        if (enemy_data->hostile == true) {

            if (is_position_in_range(enemy_nav_data->current_position,
                                     enemy_data->attack_range, player_pos)) {
                attack_player();
            } else if (is_position_in_range(enemy_nav_data->current_position,
                                            enemy_data->vision_range,
                                            player_pos)) {
                move_towards_player(enemy_nav_data->current_position,
                                    player_pos);
            }
        }
    }
}

bool EnemyAI::is_position_in_range(MapPosition central, int range,
                                   MapPosition other)
{
    return (other.i >= central.i - range && other.i <= central.i + range &&
            other.j >= central.j - range && other.j <= central.j + range);
}

void EnemyAI::attack_player()
{
    std::cout << "attacking" << std::endl;
}

void EnemyAI::move_towards_player(MapPosition enemy, MapPosition player)
{
    std::cout << "moving to" << std::endl;
}
