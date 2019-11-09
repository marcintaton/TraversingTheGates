#include "SystemManager.h"

void ECS::System::SystemManager::update_systems()
{
    for (const auto& system : sorted_active_systems) {
        system.second->update();
    }
}

void ECS::System::SystemManager::update_soted_systems_container()
{
    SortedSystems new_sorted(active_systems.begin(), active_systems.end());
    sorted_active_systems = new_sorted;
}