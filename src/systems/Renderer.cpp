#include "Renderer.h"
#include "../Globals.h"
#include "../components/CameraData.h"
#include "../components/MeshRenderData.h"
#include "../components/Transform.h"
#include "../entities/Camera.h"
#include "../matrices/Projection.h"
#include "../matrices/View.h"
#include "../meshes/Quad.h"

Renderer::Renderer()
{
    set_priority(10);
    bind_mesh(Quad());
    cached_camera_id = ECS::ECEngine::get_instance()
                           .get_entities_of_type<Camera>()[0]
                           ->get_entity_id();
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::do_on_update()
{

    update_matrices();
    render_objects();
}

void Renderer::update_matrices()
{
    auto camera_trans = ECS::ECEngine::get_instance().get_component<Transform>(
        cached_camera_id);
    auto camera_data = ECS::ECEngine::get_instance().get_component<CameraData>(
        cached_camera_id);

    view.update_matrix(window_w, window_h, camera_trans->position,
                       camera_trans->forward(), camera_trans->up());
    projection.update_matrix(screen_w, screen_h, camera_data->zoom);
}

void Renderer::render_objects()
{
    auto render_objects =
        ECS::ECEngine::get_instance()
            .get_component_cluster<Transform, MeshRenderData>();

    glBindVertexArray(VAO);
    // all rendering

    for (int i = 0; i < render_objects.cluster.size(); ++i) {
        auto mesh_render_data = render_objects.get_component<MeshRenderData>(i);
        auto transform = render_objects.get_component<Transform>(i);

        mesh_render_data->shader.use();

        GLint model_location =
            glGetUniformLocation(mesh_render_data->shader.program, "model");
        GLint view_location =
            glGetUniformLocation(mesh_render_data->shader.program, "view");
        GLint proj_location = glGetUniformLocation(
            mesh_render_data->shader.program, "projection");

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh_render_data->texture);
        glUniform1i(
            glGetUniformLocation(mesh_render_data->shader.program, "texture1"),
            0);

        glm::mat4 model(1);
        model = glm::translate(model, transform->position);

        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_location, 1, GL_FALSE,
                           glm::value_ptr(View::matrix));
        glUniformMatrix4fv(proj_location, 1, GL_FALSE,
                           glm::value_ptr(Projection::matrix));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
}

void Renderer::bind_mesh(Mesh mesh)
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.get_vertices_size(),
                 &mesh.vertices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.get_indices_size(),
                 &mesh.indices.front(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT),
                          (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    // texture cooridinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT),
                          (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
