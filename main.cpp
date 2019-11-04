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
    std::shared_ptr<AComponent> a2 =
        ECS::ECSEngine::get_instance().add_component<AComponent>(e2);
    // ComponentIterator<BComponent> b_it =
    //     ECS::ECSEngine::get_instance().get_components_of_type<BComponent>();

    // std::cout << b_it.components.size() << std::endl;

    std::bitset<5> bit1("00011");
    std::bitset<5> bit2("00010");
    std::bitset<5> bit3("01101");

    std::bitset<5> mask("01100");

    std::cout << ((mask & bit1) == mask) << std::endl;
    std::cout << ((mask & bit2) == mask) << std::endl;
    std::cout << ((mask & bit3) == mask) << std::endl;

    ComponentCluster<AComponent, BComponent> cls =
        ECS::ECSEngine::get_instance()
            .get_component_cluster<AComponent, BComponent>();

    return 0;
}