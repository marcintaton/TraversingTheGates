#pragma once

#include <algorithm>
#include <typeinfo>

#include "../../utility/typeHelper.h"
#include "IEntity.h"

namespace ECS
{
    namespace Entity
    {

        template<class T>
        class Entity : public IEntity
        {
          private:
            static const EntityTypeId ENTITY_TYPE_ID;

          public:
            Entity() {}

            virtual const EntityTypeId get_entity_type_id() const override
            {
                return ENTITY_TYPE_ID;
            }
        };

        template<class T>
        const EntityTypeId
            Entity<T>::ENTITY_TYPE_ID = utility::type::get_type_id<Entity<T>>();

        template<class T>
        const EntityTypeId get_entity_type_id()
        {
            return utility::type::get_type_id<Entity<T>>();
        }
    }; // namespace Entity
};     // namespace ECS
