#include "InteractionManager.h"

#include "../entities/GameEntities.h"
#include "../interactionLogic/GameInteractives.h"

InteractionManager::InteractionManager()
{

    logic_systems.emplace(Utility::Type::get_type_id<Wall>(),
                          std::make_shared<WallInteraction>());

    logic_systems.emplace(Utility::Type::get_type_id<Tile>(),
                          std::make_shared<TileInteraction>());

    logic_systems.emplace(Utility::Type::get_type_id<Door>(),
                          std::make_shared<DoorInteraction>());
}