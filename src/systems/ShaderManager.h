#pragma once

#include "../engine/GameEngine.h"
#include "../shaders/Shader.h"

class ShaderManager : public ECS::System::IndependentSystem<ShaderManager>
{
  private:
    void load_shaders();

  public:
    Shader core_shader;

    ShaderManager();
    virtual void on_enable() override {}
    virtual void on_disable() override {}
};
