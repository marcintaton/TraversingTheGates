#pragma once

#include <map>
#include <memory>

#include "../../utility/Logging.h"
#include "../../utility/Type.h"
#include "IndependentSystem.h"

namespace ECS
{
namespace System
{

using IndependentSystems = std::map<SystemTypeId, IndpdntSystemPtr>;

class IndependentSystemManager
{
  private:
    IndependentSystems independent_systems;

    template<class T>
    void is_system_present()
    {
        return independent_systems.find(Utility::Type::get_type_id<T>()) !=
               independent_systems.end();
    }

  public:
    template<class T>
    void create_system()
    {
        if (!is_system_present<T>()) {
            independent_systems.try_emplace(Utility::Type::get_type_id<T>(),
                                            std::make_shared<T>());

            spdlog::info(
                "ECS::System::IndependentSystemManger::create_system - "
                "Creating {0}",
                Utility::Type::get_type_name<T>());
        }
    }

    template<class T>
    void destroy_system()
    {
        if (is_system_present<T>()) {
            independent_systems.erase(Utility::Type::get_type_id<T>());

            spdlog::info(
                "ECS::System::IndepenentSystemManger::destroy_system - "
                "Destroying {0}",
                Utility::Type::get_type_name<T>());
        }
    }

    template<class T>
    void enable_system()
    {
        if (is_system_present<T>()) {
            if (!independent_systems[Utility::Type::get_type_id<T>()]
                     ->is_enabled()) {
                independent_systems[Utility::Type::get_type_id<T>()]->enabled =
                    true;
                independent_systems[Utility::Type::get_type_id<T>()]
                    ->on_enable();

                spdlog::info("ECS::System::IndependentSystemManger::enable_"
                             "system - Enabling {0}",
                             Utility::Type::get_type_name<T>());
            }
        }
    }

    template<class T>
    void disable_system()
    {
        if (is_system_present<T>()) {
            if (independent_systems[Utility::Type::get_type_id<T>()]
                    ->is_enabled()) {
                independent_systems[Utility::Type::get_type_id<T>()]->enabled =
                    false;
                independent_systems[Utility::Type::get_type_id<T>()]
                    ->on_disable();

                spdlog::info("ECS::System::IndependentSystemManger::disable_"
                             "system - Disabling {0}",
                             Utility::Type::get_type_name<T>());
            }
        }
    }
};
}; // namespace System
}; // namespace ECS