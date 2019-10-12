#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>

const auto window_w = 1600;
const auto window_h = 900;

const auto vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main(){\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}";

const auto fragmentShaderSource = "#version 330 core\n"
                                  "out vec4 color;\n"
                                  "void main(){\n"
                                  "color = vec4(1.f, 0.5f, 0.2f, 1.f);\n"
                                  "}";

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

static void adjust_ortho_on_resize(GLFWwindow* window, int width, int height)
{
    float ratio = width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1, 1, 1, -1);
    glMatrixMode(GL_MODELVIEW);
}

int main(void)
{
    // GLFW init
    auto glfw_init_result = glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if (!glfw_init_result) {
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    // window
    GLFWwindow* window =
        glfwCreateWindow(window_w, window_h, "Sample", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    // window resize
    glfwSetWindowSizeCallback(window, adjust_ortho_on_resize);
    adjust_ortho_on_resize(window, window_w, window_h);

    // GLEW init
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW INIT ERROR" << std::endl;
        exit(EXIT_FAILURE);
    }

    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // shader compilation check
    GLint success;
    GLchar infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "SHADER COMPILE ERROR: VERTEX\n" << infolog << std::endl;
    }

    // fragment shader
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // shader compilation check
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "SHADER COMPILE ERROR: FRAGMENT\n" << infolog << std::endl;
    }

    // linking shaders
    auto shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check shader linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "SHADER LINKING ERROR\n" << infolog << std::endl;
    }

    // cleneup shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // geometry
    GLuint VBO;
    GLuint VAO;
    GLfloat new_vertices[] = {-0.5f, -0.5f, 0.f,  0.5f, -0.5f,
                              0.f,   0.f,   0.5f, 0.f};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(new_vertices), new_vertices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT),
                          (GLvoid*) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POLYGON, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}