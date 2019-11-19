#include "DoorInteraction.h"

void DoorInteraction::OnKick(const Kick* event)
{
    spdlog::info("Door kicked.");
}

void DoorInteraction::OnUse(const Use* event)
{

    spdlog::info("Door used.");
}