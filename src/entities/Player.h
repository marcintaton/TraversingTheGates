#pragma once

#include <glm/glm.hpp>

#include "../engine/GameEngine.h"
#include "../shaders/Shader.h"

class Player : public ECS::Entity::Entity<Player>
{
  public:
    Player() {}
    Player(glm::vec3 _position, Shader _shader, GLuint _texture);
};