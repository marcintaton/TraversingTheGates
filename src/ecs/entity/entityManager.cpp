#include "entityManager.h"

EntityManager::EntityManager() {}

EntityManager::~EntityManager()
{
    all_entities.clear();
    entities_by_type.clear();
}

std::shared_ptr<IEntity> EntityManager::get_entity(EntityId by_id)
{
    auto e_iterator = std::find_if(
        all_entities.begin(), all_entities.end(),
        [&](const auto& entity) { return by_id == entity->get_entity_id(); });

    if (!(e_iterator == all_entities.end())) {
        return (*e_iterator);
    } else {
        std::cout << "ECS::ENTITY::ENTITY_MANAGER::GET_ENTITY::ENTITY_NOT_FOUND"
                  << std::endl;
        return 0;
    }
}

void EntityManager::remove_entity(EntityId by_id)
{
    std::shared_ptr<IEntity> temp = get_entity(by_id);
    all_entities.erase(
        std::find(all_entities.begin(), all_entities.end(), temp));
    entities_by_type[temp->get_entity_type_id()].erase(
        std::find(entities_by_type[temp->get_entity_type_id()].begin(),
                  entities_by_type[temp->get_entity_type_id()].end(), temp));
}

ComponentMask EntityManager::get_mask(EntityId from_entity)
{
    return get_entity(from_entity)->get_mask();
}

ComponentArray EntityManager::get_component_ids(EntityId from_entity)
{
    return get_entity(from_entity)->get_component_ids();
}
