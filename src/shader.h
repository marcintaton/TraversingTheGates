#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <GL/glew.h>

class Shader
{
  public:
    GLuint program;

  public:
    Shader(const GLchar* vertex_path, const GLchar* fragment_path);
    ~Shader();

    void use();
};
