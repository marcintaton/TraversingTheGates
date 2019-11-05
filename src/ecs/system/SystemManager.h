#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <type_traits>

#include "../../utility/typeHelper.h"
#include "System.h"

struct ExecutionOrderComparator {
    template<typename T>
    bool operator()(const T& l, const T& r) const
    {
        if (l.second->get_priority() != r.second->get_priority())

            return l.second->get_priority() < r.second->get_priority();

        return l.first < r.first;
    }
};

class SystemManager
{
    using SystemPtr = std::shared_ptr<ISystem>;
    using Systems = std::map<SystemTypeId, SystemPtr>;
    using IdSystemPair = std::pair<SystemTypeId, SystemPtr>;
    using SortedSystems = std::set<IdSystemPair, ExecutionOrderComparator>;

  private:
    Systems inactive_systems;
    Systems active_systems;
    SortedSystems sorted_active_systems;

    template<class T>
    bool is_system_active()
    {
        return active_systems.find(utility::type_helper::get_type_id<T>()) !=
               active_systems.end();
    }

    template<class T>
    bool is_system_inactive()
    {
        return inactive_systems.find(utility::type_helper::get_type_id<T>()) !=
               inactive_systems.end();
    }

    template<class T>
    bool is_system_present()
    {
        return is_system_active<T>() || is_system_inactive<T>();
    }

    void update_soted_systems_container()
    {
        SortedSystems new_sorted(active_systems.begin(), active_systems.end());
        sorted_active_systems = new_sorted;
    }

    void update_systems()
    {
        for (const auto& system : sorted_active_systems) {
            system.second->update();
        }
    }

  public:
    template<class T>
    void create_system()
    {
        if (!is_system_present<T>()) {
            inactive_systems.try_emplace(utility::type_helper::get_type_id<T>(),
                                         std::make_unique<T>());
        }
    }

    template<class T>
    void create_active_system()
    {
        if (!is_system_present<T>()) {
            active_systems.try_emplace(utility::type_helper::get_type_id<T>(),
                                       std::make_unique<T>());

            update_soted_systems_container();
        }
    }

    template<class T>
    void destroy_system()
    {
        if (is_system_inactive<T>()) {
            inactive_systems.erase(utility::type_helper::get_type_id<T>());
        } else if (is_system_active<T>()) {
            active_systems.erase(utility::type_helper::get_type_id<T>());
            update_soted_systems_container();
        }
    }

    template<class T>
    void enable_system()
    {
        if (is_system_inactive<T>()) {
            inactive_systems[utility::type_helper::get_type_id<T>()]
                ->on_enable();
            active_systems.insert(move(inactive_systems.extract(
                utility::type_helper::get_type_id<T>())));
            update_soted_systems_container();
        }
    }

    template<class T>
    void disable_system()
    {
        active_systems[utility::type_helper::get_type_id<T>()]->on_disable();
        if (is_system_active<T>()) {
            inactive_systems.insert(move(active_systems.extract(
                utility::type_helper::get_type_id<T>())));
            update_soted_systems_container();
        }
    }
};
