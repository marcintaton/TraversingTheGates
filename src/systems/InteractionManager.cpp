#include "InteractionManager.h"

#include "../entities/GameEntities.h"
#include "../interactionLogic/GameInteractives.h"

InteractionManager::InteractionManager()
{
    logic_systems.emplace(
        Utility::Type::get_type_id<ECS::Entity::Entity<Wall>>(),
        std::make_shared<WallInteraction>());

    logic_systems.emplace(
        Utility::Type::get_type_id<ECS::Entity::Entity<Tile>>(),
        std::make_shared<TileInteraction>());

    logic_systems.emplace(
        Utility::Type::get_type_id<ECS::Entity::Entity<Door>>(),
        std::make_shared<DoorInteraction>());

    kick_delegate = Event::EventDelegate<InteractionManager, Kick>(
        this, &InteractionManager::receive_kick);
    use_delegate = Event::EventDelegate<InteractionManager, Use>(
        this, &InteractionManager::receive_use);
}

void InteractionManager::subscribe()
{
    Event::EventEngine::get_instance().add_listener<Kick>(&kick_delegate);
    Event::EventEngine::get_instance().add_listener<Use>(&use_delegate);
}

void InteractionManager::unsubscribe()
{
    Event::EventEngine::get_instance().remove_listener<Kick>(&kick_delegate);
    Event::EventEngine::get_instance().remove_listener<Use>(&use_delegate);
}

void InteractionManager::on_enable()
{
    subscribe();
}

void InteractionManager::on_disable()
{
    unsubscribe();
}

void InteractionManager::receive_kick(const Kick* event)
{

    ECS::EntityTypeId target_type_id = ECS::ECEngine::get_instance()
                                           .get_entity(event->target)
                                           ->get_entity_type_id();

    logic_systems[target_type_id]->OnKick(event);
}

void InteractionManager::receive_use(const Use* event)
{

    ECS::EntityTypeId target_type_id = ECS::ECEngine::get_instance()
                                           .get_entity(event->target)
                                           ->get_entity_type_id();

    logic_systems[target_type_id]->OnUse(event);
}