#pragma once

#include "../LevelGeneration/LevelData.h"
#include "../LevelGeneration/MapPosition.h"
#include "../LevelGeneration/Navmesh.h"
#include "../engine/GameEngine.h"
#include "../events/GameEvents.h"
#include "../others/Direction.h"

class LevelMap : public ECS::System::IndependentSystem<LevelMap>
{
  private:
    LevelData level_data;
    Navmesh navmesh;

    Event::EventDelegate<LevelMap, TurnEnd> on_turn_end_delegate;

    void subscribe();
    void unsubscribe();

    void update_navmesh(const TurnEnd* event);

  public:
    LevelMap();
    virtual void on_enable() override;
    virtual void on_disable() override;

    void init_current_level(LevelData data);
    bool is_tile_available(int i, int j);
    bool is_tile_available(MapPosition position);
    MapPosition find_position(ECS::EntityId by_id);
    void move_dynamic_element(ECS::EntityId id, MapPosition new_position);
    ECS::EntityId get_entity_id(MapPosition from_pos);
    ECS::EntityId get_neighbour_id(ECS::EntityId central, Direction dir);
};
