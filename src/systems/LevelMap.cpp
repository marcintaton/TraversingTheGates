#include "LevelMap.h"

LevelMap::LevelMap()
{
    on_turn_end_delegate = Event::EventDelegate<LevelMap, TurnEnd>(
        this, &LevelMap::update_navmesh);
}

void LevelMap::subscribe()
{
    Event::EventEngine::get_instance().add_listener<TurnEnd>(
        &on_turn_end_delegate);
}
void LevelMap::unsubscribe()
{

    Event::EventEngine::get_instance().remove_listener<TurnEnd>(
        &on_turn_end_delegate);
}

void LevelMap::on_enable()
{
    subscribe();
}

void LevelMap::on_disable()
{
    unsubscribe();
}

void LevelMap::init_current_level(LevelData data)
{
    level_data = data;
    navmesh.create_navmesh(data);
}

bool LevelMap::is_tile_available(int i, int j)
{
    return navmesh.is_available(i, j);
}

bool LevelMap::is_tile_available(MapPosition position)
{
    return navmesh.is_available(position.i, position.j);
}

MapPosition LevelMap::find_position(ECS::EntityId by_id)
{
    return level_data.find_element_position(by_id);
}

void LevelMap::move_dynamic_element(ECS::EntityId id, MapPosition new_position)
{
    MapPosition old_pos = find_position(id);
    level_data.move_element(old_pos, new_position);
}

ECS::EntityId LevelMap::get_entity_id(MapPosition from_pos)
{
    return level_data.find_element_id(from_pos);
}

ECS::EntityId LevelMap::get_neighbour_id(ECS::EntityId central, Direction dir)
{

    MapPosition central_pos = find_position(central);

    if (central_pos.error_type == true) {
        return 0;
    }

    if (dir == Direction::UP) {
        central_pos.j += 1;
    } else if (dir == Direction::DOWN) {
        central_pos.j -= 1;
    } else if (dir == Direction::RIGHT) {
        central_pos.i += 1;
    } else if (dir == Direction::LEFT) {
        central_pos.i -= 1;
    }

    ECS::EntityId neighbour_id = get_entity_id(central_pos);

    return neighbour_id;
}

void LevelMap::update_navmesh(const TurnEnd* event)
{
    navmesh.create_navmesh(level_data);
}
