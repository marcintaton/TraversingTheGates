#include "WallInteraction.h"

void WallInteraction::OnKick(ECS::EntityId source, ECS::EntityId target)
{
    spdlog::info("Wall kicked. That probably hurt");
}

void WallInteraction::OnUse(ECS::EntityId source, ECS::EntityId target)
{
    spdlog::info("Wall used. Nothing happens");
}