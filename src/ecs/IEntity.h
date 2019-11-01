#pragma once

#include <algorithm>

using EntityId = std::size_t;
using EntityTypeId = std::size_t;

class IEntity
{
  private:
    EntityId entity_id = 5;

  public:
    IEntity() {}
    ~IEntity() {}

    inline const EntityId get_entity_id() const { return this->entity_id; }
    virtual const EntityTypeId get_entity_type_id() const = 0;
};