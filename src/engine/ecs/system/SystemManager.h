#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <type_traits>

#include "../../utility/Logging.h"
#include "../../utility/Type.h"
#include "ExecutionOrderComparator.h"
#include "System.h"

namespace ECS
{

namespace System
{
// struct ExecutionOrderComparator;
using Systems = std::map<SystemTypeId, SystemPtr>;
using IdSystemPair = std::pair<SystemTypeId, SystemPtr>;
using SortedSystems = std::set<IdSystemPair, ExecutionOrderComparator>;

class SystemManager
{

  private:
    Systems inactive_systems;
    Systems active_systems;
    SortedSystems sorted_active_systems;

    template<class T>
    bool is_system_active()
    {
        return active_systems.find(Utility::Type::get_type_id<T>()) !=
               active_systems.end();
    }

    template<class T>
    bool is_system_inactive()
    {
        return inactive_systems.find(Utility::Type::get_type_id<T>()) !=
               inactive_systems.end();
    }

    template<class T>
    bool is_system_present()
    {
        return is_system_active<T>() || is_system_inactive<T>();
    }

    void update_soted_systems_container();

    void update_systems();

  public:
    template<class T>
    void create_system()
    {
        if (!is_system_present<T>()) {
            inactive_systems.try_emplace(Utility::Type::get_type_id<T>(),
                                         std::make_shared<T>());

            spdlog::info("ECS::System::SystemManger::create_system - "
                         "Creating {0}",
                         Utility::Type::get_type_name<T>());
        }
    }

    template<class T>
    void create_active_system()
    {
        if (!is_system_present<T>()) {
            active_systems.try_emplace(Utility::Type::get_type_id<T>(),
                                       std::make_shared<T>());

            update_soted_systems_container();

            spdlog::info("ECS::System::SystemManger::create_active_system - "
                         "Creating {0}",
                         Utility::Type::get_type_name<T>());
        }
    }

    template<class T>
    void destroy_system()
    {
        if (is_system_inactive<T>()) {
            inactive_systems.erase(Utility::Type::get_type_id<T>());

            spdlog::info("ECS::System::SystemManger::destroy_system - "
                         "Destroying inactive {0}",
                         Utility::Type::get_type_name<T>());
        } else if (is_system_active<T>()) {
            active_systems.erase(Utility::Type::get_type_id<T>());
            update_soted_systems_container();

            spdlog::info("ECS::System::SystemManger::destroy_system - "
                         "Destroying active {0}",
                         Utility::Type::get_type_name<T>());
        }
    }

    template<class T>
    void enable_system()
    {
        if (is_system_inactive<T>()) {
            inactive_systems[Utility::Type::get_type_id<T>()]->on_enable();
            active_systems.insert(move(
                inactive_systems.extract(Utility::Type::get_type_id<T>())));
            update_soted_systems_container();

            spdlog::info(
                "ECS::System::SystemManger::enable_system - Enabling {0}",
                Utility::Type::get_type_name<T>());
        }
    }

    template<class T>
    void disable_system()
    {
        if (is_system_active<T>()) {
            active_systems[Utility::Type::get_type_id<T>()]->on_disable();
            inactive_systems.insert(
                move(active_systems.extract(Utility::Type::get_type_id<T>())));
            update_soted_systems_container();

            spdlog::info(
                "ECS::System::SystemManger::disable_system - Disabling {0}",
                Utility::Type::get_type_name<T>());
        }
    }
};
}; // namespace System
}; // namespace ECS
