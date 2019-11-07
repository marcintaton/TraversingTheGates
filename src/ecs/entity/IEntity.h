#pragma once

#include <algorithm>
#include <array>
#include <bitset>

#include <iostream>
#include <memory>

#include "../API.h"
#include "../component/IComponent.h"

namespace ECS
{
    namespace Entity
    {

        class IEntity;
        using EntityPtr = std::shared_ptr<IEntity>;

        inline EntityId get_new_entity_id()
        {
            static EntityId last_entity_id = 1u;
            return last_entity_id++;
        }

        class IEntity
        {
          private:
            EntityId entity_id;
            ComponentMask component_mask;
            ComponentIdArray component_ids;

          public:
            IEntity();
            ~IEntity() {}

            inline const EntityId get_entity_id() const { return entity_id; }
            virtual const EntityTypeId get_entity_type_id() const = 0;
            inline ComponentMask get_mask() { return component_mask; }
            inline ComponentIdArray get_component_ids()
            {
                return component_ids;
            }

            template<class T>
            ComponentId get_component_id()
            {
                if (has_component<T>()) {
                    return component_ids
                        [Component::read_component_type_id<T>()];
                } else {
                    std::cout << "ECS::ENTITY::IENTITY::GET_COMPONENT_ID::"
                                 "NO_COMPONENT_OF_THIS_TYPE_IN_ENTITY"
                              << std::endl;
                    return 0;
                }
            }

            template<class T>
            void add_component_info(ComponentId id)
            {
                ComponentTypeId comp_type_id =
                    Component::read_component_type_id<T>();
                component_mask[comp_type_id] = 1;
                component_ids[comp_type_id] = id;
            }

            template<class T>
            void remove_component_info()
            {
                ComponentTypeId comp_type_id =
                    Component::read_component_type_id<T>();
                component_mask[comp_type_id] = 0;
                component_ids[comp_type_id] = 0;
            }

            template<class T>
            bool has_component()
            {
                return component_mask[Component::read_component_type_id<T>()];
            }
        };
    }; // namespace Entity
};     // namespace ECS
