#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

#include "../../utility/typeHelper.h"
#include "IEntity.h"
#include "entity.h"
#include "entityIterator.h"

template<class T>
bool assert_valid_entity_type()
{
    return std::is_base_of<IEntity, T>::value;
}

class EntityManager
{
  private:
    std::map<EntityTypeId, std::vector<std::shared_ptr<IEntity>>>
        entities_by_type;
    std::vector<std::shared_ptr<IEntity>> all_entities;
    std::shared_ptr<IEntity> get_entity(EntityId by_id);

  public:
    EntityManager();
    ~EntityManager();

    template<class T>
    EntityId create_entity()
    {
        if (assert_valid_entity_type<T>()) {
            std::shared_ptr<IEntity> new_entity(new T);

            entities_by_type[new_entity->get_entity_type_id()].push_back(
                new_entity);
            all_entities.push_back(new_entity);

            return new_entity->get_entity_id();

        } else {
            std::cout << "ECS::ENTITY::ENTITY_MANAGER::CREATE_ENTITY::INVALID_"
                         "ENTITY_TYPE";
            return -1;
        }
    }

    template<class T>
    EntityIterator<T> get_entities_of_type()
    {
        return EntityIterator<T> {
            .container = entities_by_type
                [utility::type_helper::get_type_id<Entity<T>>()]};
    }

    void remove_entity(EntityId by_id);
    ComponentMask get_mask(EntityId from_entity);
    ComponentArray get_component_ids(EntityId from_entity);
};
