#include "Navmesh.h"

void Navmesh::init_from_level_data(LevelData data)
{

    for (int i = 0; i < Global::GlobalData::max_map_size; ++i) {
        for (int j = 0; j < Global::GlobalData::max_map_size; ++j) {

            if (data.base_level[i][j] != 0) {
                auto base_id = ECS::ECEngine::get_instance()
                                   .get_entity(data.base_level[i][j])
                                   ->get_entity_id();

                static_elements[i][j] =
                    ECS::ECEngine::get_instance()
                        .get_component<NavigationData>(base_id)
                        ->passable;
            } else {
                static_elements[i][j] = 1;
            }

            if (data.top_level[i][j] != 0) {
                auto top_id = ECS::ECEngine::get_instance()
                                  .get_entity(data.top_level[i][j])
                                  ->get_entity_id();

                dynamic_elements[i][j] =
                    ECS::ECEngine::get_instance()
                        .get_component<NavigationData>(top_id)
                        ->passable;
            } else {
                dynamic_elements[i][j] = 1;
            }
        }

        std::cout << dynamic_elements[i] << std::endl;
    }
}

void Navmesh::move_dynamic_element(MapPosition old_position,
                                   MapPosition new_position)
{
    dynamic_elements[old_position.i][old_position.j] = 1;
    dynamic_elements[new_position.i][new_position.j] = 0;
}