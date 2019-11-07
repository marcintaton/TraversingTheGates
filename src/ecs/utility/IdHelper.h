#pragma once

#include "../ECSAPI.h"

namespace ECS
{
    namespace Utility
    {
        namespace IdHelper
        {
            inline EntityId get_new_entity_id()
            {
                static EntityId last_entity_id = 1u;
                return last_entity_id++;
            }

            inline ComponentId get_new_component_id()
            {
                static ComponentId last_comp_id = 1u;
                return last_comp_id++;
            }

            inline ComponentId get_new_component_type_id()
            {
                static ComponentId last_comp_type_id = 0u;
                return last_comp_type_id++;
            }

            template<class T>
            inline ComponentTypeId read_component_type_id() noexcept
            {
                static ComponentTypeId comp_type_id =
                    get_new_component_type_id();
                return comp_type_id;
            }
        }; // namespace IdHelper
    };     // namespace Utility
};         // namespace ECS