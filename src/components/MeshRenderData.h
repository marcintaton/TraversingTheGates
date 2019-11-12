#pragma once

#include "../meshes/Mesh.h"
#include "../shaders/Shader.h"

#include "../engine/GameEngine.h"

struct MeshRenderData : public ECS::Component::Component<MeshRenderData> {
    Mesh mesh;
    Shader shader;
    GLuint texture;

    MeshRenderData() {}
    MeshRenderData(Mesh _mesh, Shader& _shader, GLuint _texture)
    {
        mesh = _mesh;
        shader = _shader;
        texture = _texture;
    }
};
