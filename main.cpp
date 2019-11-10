#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/engine/utility/Logging.h"
#include "src/systems/Renderer.h"

const auto window_w = 1200;
const auto window_h = 900;
int screen_w, screen_h;

void setup()
{
    Utility::Logging::setup_logger();

    // GLFW init
    auto glfw_init_result = glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if (!glfw_init_result) {
        exit(EXIT_FAILURE);
    }

    // window
    GLFWwindow* window =
        glfwCreateWindow(window_w, window_h, "Sample", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwGetFramebufferSize(window, &screen_w, &screen_h);

    glfwMakeContextCurrent(window);

    // GLEW init
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW INIT ERROR" << std::endl;
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, screen_w, screen_h);
    glEnable(GL_DEPTH_TEST);
}

void cleanup()
{
    glfwTerminate();
}

int main(void)
{

    //

    setup();

    //

    Renderer r;

    //

    cleanup();

    exit(EXIT_SUCCESS);
}