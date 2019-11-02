#include <bitset>
#include <iostream>
#include <typeinfo>
#include <vector>

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

int main(void)
{
    EntityManager entity_manager;

    EntityId new_id = entity_manager.create_entity<Enemy>();
    EntityId new_id2 = entity_manager.create_entity<Enemy>();
    EntityId new_id3 = entity_manager.create_entity<Enemy>();

    for (auto e : entity_manager.get_entities_of_type<Enemy>().container) {
        std::cout << e->get_entity_id() << std::endl;
    }

    entity_manager.remove_entity(new_id);

    for (auto e : entity_manager.get_entities_of_type<Enemy>().container) {
        std::cout << e->get_entity_id() << std::endl;
    }
    return 0;
}