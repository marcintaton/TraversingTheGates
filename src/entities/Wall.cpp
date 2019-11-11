#include "Wall.h"

#include "../components/MeshRenderData.h"
#include "../components/Transform.h"
#include "../meshes/Quad.h"

Wall::Wall(glm::vec3 _position, Shader _shader, GLuint _texture)
{
    auto transform = ECS::ECEngine::get_instance().do_add_component<Transform>(
        get_entity_id(), _position, glm::vec2(1, 1), 0.0f);
    add_component_info<Transform>(transform->get_component_id());

    auto mesh_r_data =
        ECS::ECEngine::get_instance().do_add_component<MeshRenderData>(
            get_entity_id(), Quad {}, _shader, _texture);
    add_component_info<MeshRenderData>(mesh_r_data->get_component_id());
}