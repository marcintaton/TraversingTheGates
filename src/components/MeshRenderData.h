#pragma once

#include "../meshes/Mesh.h"
#include "../shaders/Shader.h"

struct MeshRenderData {
    Mesh mesh;
    Shader shader;
    GLuint texture;
};
