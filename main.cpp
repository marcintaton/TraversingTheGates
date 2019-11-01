#include <iostream>
#include <typeinfo>

#include "src/ecs/entity.h"

int main(void)
{
    Entity<int> e1;
    Entity<bool> e2;

    std::cout << e1.get_entity_type_id() << std::endl;
    std::cout << e2.get_entity_type_id() << std::endl;

    std::cout << e2.get_entity_id() << std::endl;

    return 0;
}