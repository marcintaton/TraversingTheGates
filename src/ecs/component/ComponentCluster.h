#pragma once

#include <tuple>
#include <vector>

#include "../API.h"

namespace ECS
{
    namespace Component
    {

        template<class... Ts>
        struct ComponentCluster {

          private:
            inline void add_new_entry_to_cluster(EntityId e_id)
            {
                id_lookup.push_back(e_id);
                cluster.push_back(std::tuple<std::shared_ptr<Ts>...>());
            }

          public:
            std::vector<EntityId> id_lookup;
            std::vector<std::tuple<std::shared_ptr<Ts>...>> cluster;

            template<class T>
            void add_to_cluster(EntityId e_id, std::shared_ptr<T> component)
            {
                if (id_lookup.empty() || id_lookup.back() != e_id) {
                    add_new_entry_to_cluster(e_id);
                }

                std::get<std::shared_ptr<T>>(cluster.back()) = component;
            }

            template<class T>
            inline std::shared_ptr<T> get_component(std::size_t form_index)
            {
                return std::get<std::shared_ptr<T>>(cluster[form_index]);
            }
        };
    }; // namespace Component
};     // namespace ECS
