#pragma once

#include <algorithm>
#include <typeinfo>

#include "../../utility/typeHelper.h"
#include "IEntity.h"

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
    Entity<T>::ENTITY_TYPE_ID = type_helper::get_type_id<Entity<T>>();
