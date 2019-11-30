#include "Navmesh.h"

void Navmesh::create_navmesh(LevelData data)
{

    for (int i = 0; i < Global::GlobalData::max_map_size; ++i) {
        for (int j = 0; j < Global::GlobalData::max_map_size; ++j) {

            level[i][j].clear();

            for (auto e : data.level[i][j]) {
                if (e != 0) {
                    bool is_passable = ECS::ECEngine::get_instance()
                                           .get_component<NavigationData>(e)
                                           ->passable;
                    level[i][j].push_back(is_passable);
                } else {
                    level[i][j].push_back(1);
                }
            }
        }
    }
}