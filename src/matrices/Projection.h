#pragma once

class Projection
{
  public:
    static glm::mat4 matrix;

    void update_matrix(GLuint screen_w, GLuint screen_h, GLfloat camera_zoom);
};
