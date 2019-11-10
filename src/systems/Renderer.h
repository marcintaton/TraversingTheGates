#pragma once

#include "glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../engine/GameEngine.h"
#include "../matrices/Projection.h"
#include "../matrices/View.h"
#include "../meshes/Mesh.h"

class Renderer : public ECS::System::System<Renderer>
{

  private:
    std::size_t custom_priority = 10;
    ECS::EntityId cached_camera_id;

    GLuint VBO;
    GLuint VAO;
    GLuint EBO;

    void do_on_update();
    void update_matrices();
    void render_objects();
    void bind_mesh(Mesh mesh);

  protected:
    virtual void update() override { do_on_update(); }

  public:
    Renderer();
    ~Renderer();
};