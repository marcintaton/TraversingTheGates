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

    ecs_engine.get_component_manager()->add_component<AComponent>(e2);

    // ECSEngine::ComponentManagerAccess::get()->add_component<BComponent>(e1);

    // std::cout << ecs_engine.get_entity_manager()->get_entity(e1)->get_mask()
    //           << std::endl;
    // // std::cout << ecs_engine.get_entity_manager()->get_mask(e2) <<
    // std::endl;

    // ECSEngine::ComponentManagerAccess::get()->remove_component<AComponent>(e2);

    // std::shared_ptr<AComponent> x =
    //     ECSEngine::ComponentManagerAccess::get()->get_component<AComponent>(e2);

    // std::cout << x->a << std::endl;
    std::cout << std::endl;

    return 0;
}