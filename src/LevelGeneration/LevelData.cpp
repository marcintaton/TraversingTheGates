#include "LevelData.h"

MapPosition LevelData::find_element_position(ECS::EntityId id)
{

    for (int i = 0; i < base_level.size(); ++i) {
        for (int j = 0; j < base_level[i].size(); ++j) {

            if (base_level[i][j] == id) {
                MapPosition m {.i = i, .j = j};
                return m;
            }

            if (top_level[i][j] == id) {
                MapPosition m {.i = i, .j = j};
                return m;
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
    auto id = top_level[old_position.i][old_position.j];
    top_level[old_position.i][old_position.j] = 0;
    top_level[new_position.i][new_position.j] = id;
}