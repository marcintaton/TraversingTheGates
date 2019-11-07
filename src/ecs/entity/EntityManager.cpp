#include "EntityManager.h"

ECS::Entity::EntityManager::~EntityManager()
{
    all_entities.clear();
    entities_by_type.clear();
    entities_by_id.clear();
}

ECS::Entity::EntityPtr ECS::Entity::EntityManager::get_entity(EntityId by_id)
{
    if (!(entities_by_id[by_id] == nullptr)) {
        return entities_by_id[by_id];
    } else {
        std::cout << "ECS::ENTITY::ENTITY_MANAGER::GET_ENTITY::ENTIY_NOT_FOUND"
                  << std::endl;
        return 0;
    }
}

void ECS::Entity::EntityManager::remove_entity(EntityId by_id)
{
    EntityPtr temp = get_entity(by_id);
    all_entities.erase(
        std::find(all_entities.begin(), all_entities.end(), temp));
    entities_by_type[temp->get_entity_type_id()].erase(
        std::find(entities_by_type[temp->get_entity_type_id()].begin(),
                  entities_by_type[temp->get_entity_type_id()].end(), temp));
    entities_by_id.erase(by_id);
}

std::vector<ECS::EntityId>
ECS::Entity::EntityManager::get_eintity_ids_by_mask(ComponentMask mask)
{
    std::vector<EntityId> fitting_ids;
    for (auto entity : all_entities) {
        if ((entity->get_mask() & mask) == mask) {
            fitting_ids.push_back(entity->get_entity_id());
        }
    }
    return fitting_ids;
}

ECS::ComponentMask ECS::Entity::EntityManager::get_mask(EntityId from_entity)
{
    return get_entity(from_entity)->get_mask();
}

ECS::ComponentIdArray
ECS::Entity::EntityManager::get_component_ids(EntityId from_entity)
{
    return get_entity(from_entity)->get_component_ids();
}
