#include "Tile.h"

#include "../components/GameComponents.h"
#include "../meshes/Quad.h"
#include "../others/Random.h"

Tile::Tile(glm::vec3 _position, Shader _shader, GLuint _texture)
{
    auto transform = ECS::ECEngine::get_instance().do_add_component<Transform>(
        get_entity_id(), _position, glm::vec2(1, 1), 0.0f);
    add_component_info<Transform>(transform->get_component_id());

    auto random_tile_tex = Random::rand_range(0, 5);

    auto mesh_r_data =
        ECS::ECEngine::get_instance().do_add_component<MeshRenderData>(
            get_entity_id(), Quad {}, _shader, _texture,
            glm::vec2(random_tile_tex, 0), glm::vec2(5, 5));
    add_component_info<MeshRenderData>(mesh_r_data->get_component_id());

    auto nav = ECS::ECEngine::get_instance().do_add_component<NavigationData>(
        get_entity_id(), true);
    add_component_info<NavigationData>(nav->get_component_id());
}