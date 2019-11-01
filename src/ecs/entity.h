#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <typeinfo>

#include "IEntity.h"

constexpr std::size_t max_components = 32;

template<class T>
class Entity : public IEntity
{
  private:
    static const EntityTypeId ENTITY_TYPE_ID;

  public:
    std::bitset<max_components> component_mask;
    std::array<int, max_components> component_ids;

    virtual const EntityTypeId get_entity_type_id() const override
    {
        return ENTITY_TYPE_ID;
    }
};

template<class T>
const EntityTypeId Entity<T>::ENTITY_TYPE_ID = typeid(Entity<T>).hash_code();