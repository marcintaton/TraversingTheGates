#include "ISystem.h"

bool ECS::System::ISystem::operator<(const ISystem& other) const
{
    return execution_priority < other.execution_priority;
}