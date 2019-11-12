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

    try_cache_transforms();

    glm::vec3 offset = t_camera->position - t_player->position;

    if (offset.x > max_offset_from_player) {
        t_camera->position += glm::vec3(-1, 0, 0);
    } else if (offset.x < -max_offset_from_player) {
        t_camera->position += glm::vec3(1, 0, 0);
    } else if (offset.y > max_offset_from_player) {
        t_camera->position += glm::vec3(0, -1, 0);
    } else if (offset.y < -max_offset_from_player) {
        t_camera->position += glm::vec3(0, 1, 0);
    }
}

void CameraMovement::try_cache_transforms()
{
    if (t_camera == nullptr || t_player == nullptr) {

        auto player_id = ECS::ECEngine::get_instance()
                             .get_entities_of_type<Player>()[0]
                             ->get_entity_id();
        t_player =
            ECS::ECEngine::get_instance().get_component<Transform>(player_id);

        auto camera_id = ECS::ECEngine::get_instance()
                             .get_entities_of_type<Camera>()[0]
                             ->get_entity_id();
        t_camera =
            ECS::ECEngine::get_instance().get_component<Transform>(camera_id);
    }
}

void CameraMovement::center_on_player()
{
    try_cache_transforms();
    t_camera->position = t_player->position;
}