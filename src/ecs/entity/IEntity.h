#pragma once

#include <algorithm>
#include <array>
#include <bitset>

#include <iostream>

#include "../component/IComponent.h"

using EntityId = std::size_t;
using EntityTypeId = std::size_t;

constexpr std::size_t max_components = 32;
using ComponentMask = std::bitset<max_components>;
using ComponentIdArray = std::array<std::size_t, max_components>;

inline EntityId get_new_entity_id()
{
    static EntityId last_entity_id = 0u;
    return last_entity_id++;
}

class IEntity
{
  private:
    EntityId entity_id;
    ComponentMask component_mask;
    ComponentIdArray component_ids;

  public:
    IEntity() { entity_id = get_new_entity_id(); }
    ~IEntity() {}

    inline const EntityId get_entity_id() const { return this->entity_id; }
    virtual const EntityTypeId get_entity_type_id() const = 0;
    ComponentMask get_mask() { return component_mask; }
    ComponentIdArray get_component_ids() { return component_ids; }

    template<class T>
    void add_component_info(ComponentId id)
    {
        ComponentTypeId comp_type_id = read_component_type_id<T>();

        std::cout << comp_type_id << std::endl;
        component_mask[comp_type_id] = 1;
        component_ids[comp_type_id] = id;
    }

    template<class T>
    void remove_component_info()
    {
        ComponentTypeId comp_type_id = read_component_type_id<T>();
        component_mask[comp_type_id] = 0;
        component_ids[comp_type_id] = 0;
    }
};
