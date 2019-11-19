#include "TileInteraction.h"

void TileInteraction::OnKick(ECS::EntityId source, ECS::EntityId target)
{
    spdlog::info("Floor tile kicked. Nothing happens");
}

void TileInteraction::OnUse(ECS::EntityId source, ECS::EntityId target)
{
    spdlog::info("Floor tile used. Nothing happens");
}