#include "DoorInteraction.h"

void DoorInteraction::OnKick(ECS::EntityId source, ECS::EntityId target)
{
    spdlog::info("Door kicked.");
}

void DoorInteraction::OnUse(ECS::EntityId source, ECS::EntityId target)
{

    spdlog::info("Door used.");
}