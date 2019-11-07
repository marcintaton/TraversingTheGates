#pragma once

#include <iostream>
#include <map>
#include <type_traits>
#include <vector>

#include "../../utility/type.h"
#include "../ECSAPI.h"
#include "Entity.h"
#include "IEntity.h"

namespace ECS
{
    namespace Entity
    {

        template<class T>
        bool assert_valid_entity_type()
        {
            return std::is_base_of<IEntity, T>::value;
        }

        class EntityManager
        {
          private:
            std::map<EntityTypeId, std::vector<EntityPtr>> entities_by_type;
            std::map<EntityId, EntityPtr> entities_by_id;
            std::vector<EntityPtr> all_entities;

          public:
            EntityManager() {}
            ~EntityManager();

            template<class T, typename... T_args>
            EntityId create_entity(T_args&&... args)
            {
                if (assert_valid_entity_type<T>()) {
                    EntityPtr new_entity(new T(std::forward<T_args>(args)...));

                    entities_by_type[new_entity->get_entity_type_id()]
                        .push_back(new_entity);
                    all_entities.push_back(new_entity);

                    entities_by_id[new_entity->get_entity_id()] = new_entity;

                    return new_entity->get_entity_id();

                } else {
                    std::cout << "ECS::ENTITY::ENTITY_MANAGER::CREATE_ENTITY "
                                 "Invalid entity type";
                    return -1;
                }
            }

            template<class T>
            ECSSContainer<T> get_entities_of_type()
            {
                ECSSContainer<T> en_it;
                for (auto ent : entities_by_type
                         [utility::type::get_type_id<Entity<T>>()]) {
                    en_it.push_back(std::dynamic_pointer_cast<T>(ent));
                }

                return en_it;
            }

            void remove_entity(EntityId by_id);
            EntityPtr get_entity(EntityId by_id);
            std::vector<EntityId> get_eintity_ids_by_mask(ComponentMask mask);
            ComponentMask get_mask(EntityId from_entity);
            ComponentIdArray get_component_ids(EntityId from_entity);
        };
    }; // namespace Entity
};     // namespace ECS