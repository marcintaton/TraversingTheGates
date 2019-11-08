#include "IEntity.h"

ECS::Entity::IEntity::IEntity()
{
    entity_id = ECS::IdHelper::get_new_entity_id();
}