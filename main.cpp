#include <bitset>
#include <iostream>
#include <typeinfo>
#include <vector>

#include "src/ecs/component/component.h"
#include "src/ecs/component/componentManager.h"
#include "src/ecs/entity/entity.h"
#include "src/ecs/entity/entityManager.h"

#include "src/ecs/ECSEngine.h"

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

    EntityId e1 = ECSEngine::entity_manager()->create_entity<Player>();
    EntityId e2 = ECSEngine::entity_manager()->create_entity<Player>();

    // e_manager.remove_entity(e1);

    // ECSEngine::.add_component<BComponent>(e2);
    ECSEngine::component_manager()->add_component<AComponent>(e2);
    ECSEngine::component_manager()->add_component<BComponent>(e1);

    return 0;
}