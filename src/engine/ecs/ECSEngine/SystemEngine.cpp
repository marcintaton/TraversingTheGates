#include "SystemEngine.h"

ECS::SystemEngine::SystemEngine()
{
    system_manager = std::make_unique<ECS::System::SystemManager>();
    independent_system_manager =
        std::make_unique<ECS::System::IndependentSystemManager>();
}