#include <shader.h>
#include <stdexcept>
#include <iostream>

Shader::Shader(const std::string &source, GLenum shader_type)
    : shaderSource(source.c_str())
{
    switch (shader_type) {
    case GL_VERTEX_SHADER:
        shader = glCreateShader(GL_VERTEX_SHADER);
        break;
    case GL_FRAGMENT_SHADER:
        shader = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    case GL_GEOMETRY_SHADER:
        shader = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    default:
        throw std::invalid_argument("Received invalid shader type");
    }
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    compileCheckErrors();
}

void Shader::compileCheckErrors()
{
    int success, length;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char info_log[length];
        glGetShaderInfoLog(shader, length, nullptr, info_log);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED" << std::endl
                  << info_log << std::endl;
    }
}