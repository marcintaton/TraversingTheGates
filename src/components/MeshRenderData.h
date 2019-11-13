#pragma once

#include "../meshes/Mesh.h"
#include "../shaders/Shader.h"
#include "../textures/Texture.h"

#include "../engine/GameEngine.h"

struct MeshRenderData : public ECS::Component::Component<MeshRenderData> {
    Mesh mesh;
    Shader shader;
    Texture texture;

    MeshRenderData() {}
    MeshRenderData(Mesh _mesh, Shader& _shader, GLuint _texture)
    {
        mesh = _mesh;
        shader = _shader;
        texture.texture_index = _texture;
        texture.atlas_offset = glm::vec2(0, 0);
        texture.atlas_size = glm::vec2(1, 1);
    }

    MeshRenderData(Mesh _mesh, Shader& _shader, GLuint _texture,
                   glm::vec2 tex_offset, glm::vec2 atlas_size)
    {
        mesh = _mesh;
        shader = _shader;
        texture.texture_index = _texture;
        texture.atlas_offset = tex_offset;
        texture.atlas_size = atlas_size;
    }
};
