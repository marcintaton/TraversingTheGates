#include <bitset>
#include <iostream>
#include <typeinfo>
#include <vector>

#include "src/ecs/component/component.h"
// #include "src/ecs/component/componentManager.h"
#include "src/ecs/entity/entity.h"
// #include "src/ecs/entity/entityManager.h"

#include "src/ecs/ECSEngine/ComponentManagerAccess.h"
#include "src/ecs/ECSEngine/EntityManagerAccess.h"

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

int main(void)
{

    EntityId e1 =
        ECSEngine::EntityManagerAccess::get()->create_entity<Player>();
    EntityId e2 =
        ECSEngine::EntityManagerAccess::get()->create_entity<Player>();

    ECSEngine::ComponentManagerAccess::get()->add_component<AComponent>(e2);
    ECSEngine::ComponentManagerAccess::get()->add_component<BComponent>(e1);

    std::cout << ECSEngine::EntityManagerAccess::get()->get_mask(e1)
              << std::endl;
    std::cout << ECSEngine::EntityManagerAccess::get()->get_mask(e2)
              << std::endl;

    return 0;
}