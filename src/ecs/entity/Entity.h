#pragma once

#include <algorithm>
#include <typeinfo>

#include "../../utility/Type.h"
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

    virtual inline const EntityTypeId get_entity_type_id() const override
    {
        return ENTITY_TYPE_ID;
    }
};

template<class T>
const EntityTypeId
    Entity<T>::ENTITY_TYPE_ID = Utility::Type::get_type_id<Entity<T>>();

}; // namespace Entity
}; // namespace ECS
