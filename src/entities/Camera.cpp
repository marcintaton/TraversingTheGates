#include "Camera.h"

#include "../components/CameraData.h"
#include "../components/Transform.h"

Camera::Camera(glm::vec3 _position)
{
    auto transform = ECS::ECEngine::get_instance().do_add_component<Transform>(
        get_entity_id(), _position, glm::vec2(1, 1), 0.0f);
    add_component_info<Transform>(transform->get_component_id());

    auto camera_data =
        ECS::ECEngine::get_instance().do_add_component<CameraData>(
            get_entity_id());
    add_component_info<CameraData>(camera_data->get_component_id());
}