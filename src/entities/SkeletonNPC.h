#pragma once

#include <glm/glm.hpp>

#include "../engine/GameEngine.h"
#include "../shaders/Shader.h"

class SkeletonNPC : public ECS::Entity::Entity<SkeletonNPC>
{
  public:
    SkeletonNPC() {}
    SkeletonNPC(glm::vec3 _position, Shader _shader, GLuint _texture);
};