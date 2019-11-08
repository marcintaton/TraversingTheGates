#pragma once

#include <algorithm>
#include <memory>

#include "../ECSAPI.h"
#include "../utility/IdHelper.h"

namespace ECS
{
namespace Component
{
class IComponent;
using ComponentPtr = std::shared_ptr<Component::IComponent>;
using ComponentArray = std::array<ComponentPtr, max_components>;

class IComponent
{
  private:
    ComponentId component_id;

  public:
    IComponent();
    ~IComponent() {}

    inline const ComponentId get_component_id() const
    {
        return this->component_id;
    }
    virtual const ComponentTypeId get_component_type_id() const = 0;
};
}; // namespace Component
}; // namespace ECS