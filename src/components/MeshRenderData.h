#pragma once

#include "../meshes/Mesh.h"
#include "../shaders/Shader.h"

#include "../engine/GameEngine.h"

struct MeshRenderData : ECS::Component::Component<MeshRenderData> {
    Mesh mesh;
    Shader shader;
    GLuint texture;
};
