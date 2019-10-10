#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void)
{
    auto glfw_init_result = glfwInit();

    if (!glfw_init_result) {
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(1600, 900, "Sample", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        int width;
        int height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1, 1, 1, -1);
        glMatrixMode(GL_MODELVIEW);

        glBegin(GL_POLYGON);
        glVertex3f(-0.5f, -0.5f, 0.f);
        glVertex3f(0.5f, -0.5f, 0.f);
        glVertex3f(0.5f, 0.5f, 0.f);
        glVertex3f(-0.5f, 0.5f, 0.f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}