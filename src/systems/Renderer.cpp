#include "Renderer.h"

#include <math.h>
#include <chrono> 

#include "../components/GameComponents.h"
#include "../entities/GameEntities.h"
#include "../global/GlobalGLData.h"
#include "../meshes/Quad.h"

Renderer::Renderer()
{
    set_priority(10);
    cached_camera_id = ECS::ECEngine::get_instance()
                           .get_entities_of_type<Camera>()[0]
                           ->get_entity_id();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind quad mesh
    glBindVertexArray(VAO);
    bind_mesh(Quad {});
    glBindVertexArray(0);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(VAO);
    render_objects();
    glBindVertexArray(0);
    glfwSwapBuffers(Global::GlobalGLData::get_instance().window);
}

void Renderer::update_matrices()
{
    auto camera_trans = ECS::ECEngine::get_instance().get_component<Transform>(
        cached_camera_id);
    auto camera_data = ECS::ECEngine::get_instance().get_component<CameraData>(
        cached_camera_id);

    view.update_matrix(Global::GlobalGLData::get_instance().window_w,
                       Global::GlobalGLData::get_instance().window_h,
                       camera_trans->position, camera_trans->forward(),
                       camera_trans->up());
    projection.update_matrix(Global::GlobalGLData::get_instance().screen_w,
                             Global::GlobalGLData::get_instance().screen_h,
                             camera_data->zoom);
}

void Renderer::render_objects()
{
    ///
    auto start = std::chrono::high_resolution_clock::now();
    ///

    auto render_objects =
        ECS::ECEngine::get_instance()
            .get_component_cluster<Transform, MeshRenderData>();

    ///
    auto post_cluster = std::chrono::high_resolution_clock::now();
    ///

    ///

    for (int i = 0; i < render_objects.cluster.size(); ++i) {

        auto mesh_render_data = render_objects.get_component<MeshRenderData>(i);
        auto transform = render_objects.get_component<Transform>(i);

        // use shader
        if (mesh_render_data->shader.program != prev_dc_data.shader_program) {
            mesh_render_data->shader.use();
            prev_dc_data.shader_program = mesh_render_data->shader.program;
        }

        // bind texture
        if (mesh_render_data->texture.texture_index !=
            prev_dc_data.texture_index) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,
                          mesh_render_data->texture.texture_index);
            glUniform1i(glGetUniformLocation(mesh_render_data->shader.program,
                                             "texture1"),
                        0);
            prev_dc_data.texture_index =
                mesh_render_data->texture.texture_index;
        }

        // apply position, rotation and scale from transform to model matrix
        glm::mat4 model(1);
        model = glm::translate(model, transform->position);
        // convert to radians. There is a bug in glm or its documentation
        GLfloat angle = transform->rotation * (M_PI / 180.0f);
        model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
        glm::vec3 scale =
            glm::vec3(transform->scale.x, transform->scale.y, 1.0f);
        model = glm::scale(model, scale);

        // get uniforms locations
        GLint model_location =
            glGetUniformLocation(mesh_render_data->shader.program, "model");
        GLint view_location =
            glGetUniformLocation(mesh_render_data->shader.program, "view");
        GLint proj_location = glGetUniformLocation(
            mesh_render_data->shader.program, "projection");
        GLuint tex_offset_location = glGetUniformLocation(
            mesh_render_data->shader.program, "tex_offset");
        GLuint atlas_size_location = glGetUniformLocation(
            mesh_render_data->shader.program, "atlas_size");

        // set uniforms in shader
        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_location, 1, GL_FALSE,
                           glm::value_ptr(view.matrix));
        glUniformMatrix4fv(proj_location, 1, GL_FALSE,
                           glm::value_ptr(projection.matrix));
        glUniform2fv(tex_offset_location, 1,
                     glm::value_ptr(mesh_render_data->texture.atlas_offset));
        glUniform2fv(atlas_size_location, 1,
                     glm::value_ptr(mesh_render_data->texture.atlas_size));

        // draw call
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    ///
    auto post_rendering = std::chrono::high_resolution_clock::now();
    ///
    auto duration_cluster = std::chrono::duration_cast<std::chrono::microseconds>(post_cluster - start); 
    auto duration_rendering = std::chrono::duration_cast<std::chrono::microseconds>(post_rendering - post_cluster); 
    auto total_duration = duration_cluster + duration_rendering; 

    std::cout << total_duration.count() << ", " << duration_cluster.count() << ", " << duration_rendering.count() << std::endl;
}

void Renderer::bind_mesh(Mesh mesh)
{

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
}
