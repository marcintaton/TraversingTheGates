#include <bitset>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

#include "src/ecs/component/component.h"
#include "src/ecs/component/componentIterator.h"
// #include "src/ecs/component/componentManager.h"
#include "src/ecs/entity/entity.h"
// #include "src/ecs/entity/entityManager.h"
#include "src/ecs/component/componentCluster.h"

#include "src/ecs/ECSEngine/ECSEngine.h"

class Player : public Entity<Player>
{
};

class Enemy : public Entity<Enemy>
{
  public:
    Enemy() : Entity<Enemy>() {}
    Enemy(Player p, int b) : Entity<Enemy>()
    {
        std::cout << p.get_entity_id() + b << std::endl;
    }
};

class AComponent : public Component<AComponent>
{
  public:
    int a = 102;
    AComponent() {}
    AComponent(int _a) { a = _a; }
};

class BComponent : public Component<BComponent>
{
  public:
    bool b = true;
};

int main(void)
{

    EntityId e1 = ECS::ECSEngine::get_instance().create_entity<Player>();
    EntityId e2 = ECS::ECSEngine::get_instance().create_entity<Player>();

    std::shared_ptr<AComponent> a1 =
        ECS::ECSEngine::get_instance().add_component<AComponent>(e1);
    std::shared_ptr<BComponent> b1 =
        ECS::ECSEngine::get_instance().add_component<BComponent>(e1);
    std::shared_ptr<BComponent> b2 =
        ECS::ECSEngine::get_instance().add_component<BComponent>(e2);

    ComponentIterator<BComponent> b_it =
        ECS::ECSEngine::get_instance().get_components_of_type<BComponent>();

    std::cout << b_it.components.size() << std::endl;

    std::cout << std::endl;

    ComponentCluster<int, bool> cls;

    for (int i = 0; i < 10; i++) {
        cls.cluster.push_back({i, i % 2});
    }

    for (auto entity_info : cls.cluster) {
        std::cout << std::get<int>(entity_info) << " "
                  << std::get<bool>(entity_info) << std::endl;
    }

    return 0;
}