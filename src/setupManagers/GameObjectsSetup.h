#pragma once

#include "../engine/GameEngine.h"

#include "../entities/Tile.h"

void setupGameObjects()
{
    ECS::ECEngine::get_instance().create_entity<Tile>();
}