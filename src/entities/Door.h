#pragma once

#include <glm/glm.hpp>

#include "../engine/GameEngine.h"
#include "../shaders/Shader.h"

class Door : public ECS::Entity::Entity<Door>
{
  private:
    int open_weight = 1;
    int closed_weight = 10;
    int locked_weight = 10;
    glm::vec2 sturdiness_range = glm::vec2(1, 3);

  public:
    Door() {}
    Door(glm::vec3 _position, Shader _shader, GLuint _texture,
         bool is_vertical);
};