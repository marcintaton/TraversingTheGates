#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
    load_shaders();
}

void ShaderManager::load_shaders()
{
    core_shader = Shader("assets/shaders/tex_atlased_core.vs",
                         "assets/shaders/transparency.fs");
}