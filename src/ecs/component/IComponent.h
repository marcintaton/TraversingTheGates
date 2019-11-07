#pragma once

#include <algorithm>
#include <memory>

#include "../API.h"

namespace ECS
{
    namespace Component
    {

        class IComponent;
        using ComponentPtr = std::shared_ptr<IComponent>;
        using ComponentArray = std::array<ComponentPtr, max_components>;

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
            static ComponentTypeId comp_type_id = get_new_component_type_id();
            return comp_type_id;
        }

        class IComponent
        {
          private:
            ComponentId component_id;

          public:
            IComponent();
            ~IComponent() {}

            inline const ComponentId get_component_id() const
            {
                return this->component_id;
            }
            virtual const ComponentTypeId get_component_type_id() const = 0;
        };
    }; // namespace Component
};     // namespace ECS