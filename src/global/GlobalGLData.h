#pragma once

#include <GLFW/glfw3.h>

namespace Global
{

class GlobalGLData
{
    // Singleton
  public:
    static GlobalGLData& get_instance()
    {
        static GlobalGLData instance;
        return instance;
    }

  private:
    GlobalGLData() {}
    GlobalGLData(GlobalGLData const&) = delete;
    void operator=(GlobalGLData const&) = delete;

    //

  public:
    const uint window_w = 1200;
    const uint window_h = 900;
    int screen_w;
    int screen_h;
    GLFWwindow* window;
};
}; // namespace Global