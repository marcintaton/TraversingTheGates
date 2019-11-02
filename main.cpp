#include <bitset>
#include <iostream>
#include <typeinfo>
#include <vector>

// #include "src/ecs/component/component.h"
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

// class AComponent : public Component<AComponent>
// {
//   public:
//     int a = 102;
// };

// class BComponent : public Component<BComponent>
// {
//   public:
//     bool b = true;
// };

int main(void)
{
    EntityManager mangaer;

    EntityId e1 = mangaer.create_entity<Player>();
    EntityId e2 = mangaer.create_entity<Player>();
    EntityId e3 = mangaer.create_entity<Player>();

    mangaer.remove_entity(e1);

    return 0;
}