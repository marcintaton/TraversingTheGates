#pragma once

#include "IComponent.h"

namespace ECS
{
    namespace Component
    {
        template<typename T>
        class Component : public IComponent
        {
          private:
            static const ComponentTypeId COMPONENT_TYPE_ID;

          public:
            Component() {}

            virtual inline const ComponentTypeId
            get_component_type_id() const override
            {
                return COMPONENT_TYPE_ID;
            }
        };

        template<class T>
        const ComponentTypeId Component<T>::COMPONENT_TYPE_ID =
            ECS::Utility::IdHelper::read_component_type_id<T>();
    }; // namespace Component
};     // namespace ECS
