#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
    load_shaders();
}

void ShaderManager::load_shaders()
{
    core_shader = Shader("assets/shaders/core.vs", "assets/shaders/core.fs");
}