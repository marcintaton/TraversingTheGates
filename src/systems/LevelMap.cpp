#include "LevelMap.h"

LevelMap::LevelMap() {}

void LevelMap::init_current_level(LevelData data)
{
    level_data = data;
    navmesh.init_from_level_data(data);
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
    navmesh.move_dynamic_element(old_pos, new_position);
}
