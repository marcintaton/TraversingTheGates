#include "CameraMovement.h"

CameraMovement::CameraMovement()
{
    movement_delegate = Event::EventDelegate<CameraMovement, PlayerMoved>(
        this, &CameraMovement::move_camera);
}

void CameraMovement::subscribe()
{
    Event::EventEngine::get_instance().add_listener<PlayerMoved>(
        &movement_delegate);
}

void CameraMovement::unsubscribe()
{
    Event::EventEngine::get_instance().remove_listener<PlayerMoved>(
        &movement_delegate);
}

void CameraMovement::on_enable()
{
    subscribe();
}

void CameraMovement::on_disable()
{
    unsubscribe();
}

void CameraMovement::move_camera(const PlayerMoved* event)
{

    auto player_id = ECS::ECEngine::get_instance()
                         .get_entities_of_type<Player>()[0]
                         ->get_entity_id();
    auto player_transform =
        ECS::ECEngine::get_instance().get_component<Transform>(player_id);

    auto camera_id = ECS::ECEngine::get_instance()
                         .get_entities_of_type<Camera>()[0]
                         ->get_entity_id();
    auto camera_transform =
        ECS::ECEngine::get_instance().get_component<Transform>(camera_id);

    camera_transform->position = player_transform->position;
}