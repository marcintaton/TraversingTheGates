#pragma once

#include "../components/MeshRenderData.h"
#include "../components/Transform.h"
#include "../engine/GameEngine.h"

class Tile : public ECS::Entity::Entity<Tile>
{
  private:
  public:
    Tile()
    {
        ECS::ECEngine::get_instance().add_component<Transform>(get_entity_id());
        ECS::ECEngine::get_instance().add_component<MeshRenderData>(
            get_entity_id());
    }
};