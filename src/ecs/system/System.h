#pragma once

#include "../../utility/type.h"
#include "ISystem.h"

namespace ECS
{
    namespace System
    {
        template<class T>
        class System : public ISystem
        {
          protected:
            virtual void update() {}

          public:
            static const SystemTypeId SYSTEM_TYPE_ID;
            System() : ISystem(SYSTEM_TYPE_ID) {}
            virtual void on_enable() override {}
            virtual void on_disable() override {}
        };

        template<class T>
        const SystemTypeId
            System<T>::SYSTEM_TYPE_ID = utility::type::get_type_id<System<T>>();
    }; // namespace System
};     // namespace ECS
