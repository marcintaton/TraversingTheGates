#include <bitset>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

#include "src/ecs/component/component.h"
// #include "src/ecs/component/componentManager.h"
#include "src/ecs/entity/entity.h"
// #include "src/ecs/entity/entityManager.h"

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

ECS::ECSEngine ecs_engine;

int main(void)
{

    EntityId e1 = ecs_engine.get_entity_manager()->create_entity<Player>();
    EntityId e2 = ecs_engine.get_entity_manager()->create_entity<Player>();

    std::shared_ptr<AComponent> a1 = ecs_engine.add_component<AComponent>(e1);
    std::shared_ptr<BComponent> b2 = ecs_engine.add_component<BComponent>(e1);

    std::cout << a1->a << std::endl;

    // ecs_engine.get_component_manager()->add_component<AComponent>(e2);
    // ecs_engine.get_component_manager()->add_component<BComponent>(e2);

    std::cout << std::endl;

    return 0;
}