#pragma once

#include "../LevelGeneration/LevelData.h"
#include "../LevelGeneration/MapPosition.h"
#include "../LevelGeneration/Navmesh.h"
#include "../engine/GameEngine.h"

class LevelMap : public ECS::System::IndependentSystem<LevelMap>
{
  private:
    LevelData level_data;
    Navmesh navmesh;

  public:
    LevelMap();

    void init_current_level(LevelData data);
    bool is_tile_available(int i, int j);
    bool is_tile_available(MapPosition position);
    MapPosition find_position(ECS::EntityId by_id);
    void move_dynamic_element(ECS::EntityId id, MapPosition new_position);
};
