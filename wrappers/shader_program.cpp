#include <shader_program.h>
#include <iostream>

ShaderProgram::ShaderProgram(std::initializer_list<GLuint> t)
{
    program = glCreateProgram();
    for (const auto &x : t) {
        glAttachShader(program, x);
    }
    glLinkProgram(program);
    linkCheckErrors();
    for (const auto &x : t) {
        glDeleteShader(x);
    }
}

void ShaderProgram::linkCheckErrors()
{
    int success;
    char info_log[1024];
    glGetProgramiv(program, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, nullptr, info_log);
        std::cout << "ERROR::SHADER::LINKING_FAILED" << std::endl
                  << info_log << std::endl;
    }
}