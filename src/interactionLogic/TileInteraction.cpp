#include "TileInteraction.h"

void TileInteraction::OnKick(const Kick* event)
{
    spdlog::info("Floor tile kicked. Nothing happens");
}

void TileInteraction::OnUse(const Use* event)
{
    spdlog::info("Floor tile used. Nothing happens");
}