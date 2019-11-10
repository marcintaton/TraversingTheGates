#include "Renderer.h"
#include "../meshes/Quad.h"

Renderer::Renderer()
{
    set_priority(10);
    bind_mesh(Quad());
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::do_on_update() {}

void Renderer::update_matrices() {}

void Renderer::render_objects() {}

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
