#include "Door.h"

#include "../components/GameComponents.h"
#include "../meshes/Quad.h"

Door::Door(glm::vec3 _position, Shader _shader, GLuint _texture,
           bool is_vertical)
{
    auto transform = ECS::ECEngine::get_instance().do_add_component<Transform>(
        get_entity_id(), _position, glm::vec2(1, 1), 0.0f);
    add_component_info<Transform>(transform->get_component_id());

    glm::vec2 open_tex_index;
    glm::vec2 closed_tex_index;

    if (is_vertical) {
        open_tex_index = glm::vec2(4, 1);
        closed_tex_index = glm::vec2(3, 1);
    } else {
        open_tex_index = glm::vec2(2, 1);
        closed_tex_index = glm::vec2(1, 1);
    }

    int random_state = rand() % (open_weight + closed_weight + locked_weight);

    bool closed = true;
    bool locked = true;
    int sturdiness = rand() % (int) (sturdiness_range.y - sturdiness_range.x) +
                     sturdiness_range.x;

    glm::vec2 starting_tex = closed_tex_index;
    if (random_state < open_weight) {
        closed = false;
        locked = false;
        starting_tex = open_tex_index;
    } else if (random_state < open_weight + closed_weight) {
        closed = true;
        locked = false;
    }

    auto mesh_r_data =
        ECS::ECEngine::get_instance().do_add_component<MeshRenderData>(
            get_entity_id(), Quad {}, _shader, _texture, starting_tex,
            glm::vec2(5, 5));
    add_component_info<MeshRenderData>(mesh_r_data->get_component_id());

    auto nav = ECS::ECEngine::get_instance().do_add_component<NavigationData>(
        get_entity_id(), !closed);
    add_component_info<NavigationData>(nav->get_component_id());

    auto door_data = ECS::ECEngine::get_instance().do_add_component<DoorData>(
        get_entity_id(), closed, locked, sturdiness, open_tex_index,
        closed_tex_index);
    add_component_info<DoorData>(door_data->get_component_id());
}