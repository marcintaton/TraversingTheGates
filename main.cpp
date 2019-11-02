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
    Enemy(int a, int b) : Entity<Enemy>() { std::cout << a + b << std::endl; }
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
    EntityId e3 = mangaer.create_entity<Enemy>(1, 2);

    mangaer.remove_entity(e1);

    return 0;
}