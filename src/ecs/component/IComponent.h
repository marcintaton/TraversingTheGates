#pragma once

#include <algorithm>

using ComponentId = std::size_t;
using ComponentTypeId = std::size_t;

inline ComponentId get_new_component_id()
{
    static ComponentId last_comp_id = 1u;
    return last_comp_id++;
}

inline ComponentId get_new_component_type_id()
{
    static ComponentId last_comp_type_id = 0u;
    return last_comp_type_id++;
}

template<class T>
inline ComponentTypeId read_component_type_id() noexcept
{
    static ComponentTypeId comp_type_id = get_new_component_type_id();
    return comp_type_id;
}

class IComponent
{
  private:
    ComponentId component_id;

  public:
    IComponent() { component_id = get_new_component_id(); }
    ~IComponent() {}

    inline const ComponentId get_component_id() const
    {
        return this->component_id;
    }
    virtual const ComponentTypeId get_component_type_id() const = 0;
};