#pragma once

#include "../engine/GameEngine.h"
#include "../shaders/Shader.h"

class ShaderManager : public ECS::System::System<ShaderManager>
{
  private:
    void load_shaders();

  public:
    Shader core_shader;

    ShaderManager();
};
