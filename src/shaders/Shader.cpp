#include "Shader.h"

Shader::Shader() {}

Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path)
{
    // load shaders form files
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vertex_file;
    std::ifstream fragment_file;

    vertex_file.exceptions(std::ifstream::badbit);
    vertex_file.exceptions(std::ifstream::badbit);

    try {
        vertex_file.open(vertex_path);
        fragment_file.open(fragment_path);

        std::stringstream vertex_stream;
        std::stringstream fragmant_stream;

        vertex_stream << vertex_file.rdbuf();
        fragmant_stream << fragment_file.rdbuf();

        vertex_file.close();
        fragment_file.close();

        vertex_code = vertex_stream.str();
        fragment_code = fragmant_stream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_READ_FAILURE" << std::endl;
    }

    auto c_vertex_code = vertex_code.c_str();
    auto c_framgent_code = fragment_code.c_str();

    // compile shaders
    GLuint vertex;
    GLuint fragment;
    GLint success;
    GLchar info_log[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &c_vertex_code, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::SHADER_COMPILE_ERROR\n"
                  << info_log << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &c_framgent_code, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, info_log);

        std::cout << "ERROR::SHADER::FRAGMENT::SHADER_COMPILE_ERROR\n"
                  << info_log << std::endl;
    }

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM_LINKING_ERROR\n"
                  << info_log << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {}

void Shader::use()
{
    glUseProgram(program);
}