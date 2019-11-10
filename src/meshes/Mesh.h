#pragma once

#include <GLFW/glfw3.h>
#include <vector>

struct Mesh {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    inline GLsizeiptr get_vertices_size()
    {
        return vertices.size() * sizeof(GLfloat);
    }

    inline GLsizeiptr get_indices_size()
    {
        return indices.size() * sizeof(GLuint);
    }
};