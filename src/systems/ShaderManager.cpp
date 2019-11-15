#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
    load_shaders();
}

void ShaderManager::load_shaders()
{
    core_sh = Shader("assets/shaders/core.vs", "assets/shaders/core.fs");

    basic_sh = Shader("assets/shaders/tex_atlased_core.vs",
                      "assets/shaders/transparency.fs");
}