#include "SystemUpdateInvoker.h"

#include "../../GameEngine.h"

void ECS::System::SystemUpdateInvoker::update_systems()
{
    ECS::SystemEngine::get_instance().system_manager->update_systems();
}