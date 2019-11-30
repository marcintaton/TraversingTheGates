#include "LevelData.h"

MapPosition LevelData::find_element_position(ECS::EntityId id)
{

    for (int i = 0; i < level.size(); ++i) {
        for (int j = 0; j < level[i].size(); ++j) {
            for (auto e : level[i][j]) {
                if (e == id) {
                    MapPosition m {.i = i, .j = j};
                    return m;
                }
            }
        }
    }

    MapPosition m {.error_type = true};
    return m;
}

void LevelData::move_element(ECS::EntityId id, MapPosition new_position)
{
    MapPosition old_position = find_element_position(id);
    move_element(old_position, new_position);
}

void LevelData::move_element(MapPosition old_position, MapPosition new_position)
{
    level[new_position.i][new_position.j].push_back(
        level[old_position.i][old_position.j].back());
    level[old_position.i][old_position.j].pop_back();
}

ECS::EntityId LevelData::find_element_id(MapPosition position)
{
    if (level[position.i][position.j].size() != 0) {
        return level[position.i][position.j].back();
    } else {
        return 0;
    }
}