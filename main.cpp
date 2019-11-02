#include <bitset>
#include <iostream>
#include <typeinfo>
#include <vector>

#include "src/ecs/component/component.h"
#include "src/ecs/entity/entity.h"
#include "src/ecs/entity/entityManager.h"

class Enemy : public Entity<Enemy>
{
  public:
    Enemy() : Entity<Enemy>() {}
};

class Player : public Entity<Player>
{
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

    AComponent a1, a2;
    BComponent b1;
    std::cout << std::endl;

    std::cout << b1.get_component_type_id() << std::endl;
    std::cout << a1.get_component_type_id() << std::endl;
    std::cout << a2.get_component_type_id() << std::endl;

    std::cout << std::endl;

    // BComponent b2;

    // std::cout << b2.get_component_type_id() << std::endl;

    // Enemy e1;
    // Player p1, p2;

    // std::cout << e1.get_entity_type_id() << std::endl;
    // std::cout << p1.get_entity_type_id() << std::endl;
    // std::cout << p2.get_entity_type_id() << std::endl;

    return 0;
}