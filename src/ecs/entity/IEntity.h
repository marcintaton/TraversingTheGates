#pragma once

#include <algorithm>

using EntityId = std::size_t;
using EntityTypeId = std::size_t;

class IEntity
{
  protected:
    EntityId entity_id;
    virtual void set_entity_id(EntityId id) { entity_id = id; }

  public:
    IEntity() {}
    ~IEntity() {}

    inline const EntityId get_entity_id() const { return this->entity_id; }
    virtual const EntityTypeId get_entity_type_id() const = 0;
};