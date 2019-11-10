#pragma once

#include <GLFW/glfw3.h>
#include <vector>

struct Mesh {
    std::vector<GLfloat> vertices;
    std::vector<Gluint> indices;

    inline GLsizeiptr get_vertices_size()
    {
        return vertices.size() * sizeof(vertices);
    }

    inline GLsizeiptr get_indices_size()
    {
        return indices.size() * sizeof(indices);
    }
};