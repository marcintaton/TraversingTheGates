#include "SkeletonNPC.h"

#include "../components/GameComponents.h"
#include "../meshes/Quad.h"

SkeletonNPC::SkeletonNPC(glm::vec3 _position, Shader _shader, GLuint _texture)
{
    auto transform = ECS::ECEngine::get_instance().do_add_component<Transform>(
        get_entity_id(), _position, glm::vec2(0.6, 0.6), 0.0f);
    add_component_info<Transform>(transform->get_component_id());

    auto mesh_r_data =
        ECS::ECEngine::get_instance().do_add_component<MeshRenderData>(
            get_entity_id(), Quad {}, _shader, _texture, glm::vec2(0, 0),
            glm::vec2(4, 1));
    add_component_info<MeshRenderData>(mesh_r_data->get_component_id());

    auto nav = ECS::ECEngine::get_instance().do_add_component<NavigationData>(
        get_entity_id(), false, _position.x, _position.y);
    add_component_info<NavigationData>(nav->get_component_id());

    auto ortd_sprt =
        ECS::ECEngine::get_instance().do_add_component<OrientedSprite>(
            get_entity_id(), glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(2, 0),
            glm::vec2(3, 0));
    add_component_info<OrientedSprite>(ortd_sprt->get_component_id());

    auto enemy_data =
        ECS::ECEngine::get_instance().do_add_component<EnemyNPCData>(
            get_entity_id(), 2, 1, true);
    add_component_info<EnemyNPCData>(enemy_data->get_component_id());
}