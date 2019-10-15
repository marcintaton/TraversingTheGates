#include "gameObject.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "projection.h"
#include "view.h"

GameObject::GameObject(/* args */) {}

GameObject::GameObject(Transform transform, Material material, Mesh mesh)
{
    this->transform = transform;
    this->material = material;
    this->mesh = mesh;
}

GameObject::~GameObject() {}

void GameObject::render()
{
    material.shader.use();

    GLint model_location =
        glGetUniformLocation(material.shader.program, "model");
    GLint view_location = glGetUniformLocation(material.shader.program, "view");
    GLint proj_location =
        glGetUniformLocation(material.shader.program, "projection");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, material.texture);
    glUniform1i(glGetUniformLocation(material.shader.program, "texture1"), 0);

    glm::mat4 model(1);
    model = glm::translate(model, transform.position * 100.0f);

    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(view_location, 1, GL_FALSE,
                       glm::value_ptr(View::matrix));
    glUniformMatrix4fv(proj_location, 1, GL_FALSE,
                       glm::value_ptr(Projection::matrix));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
