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
}

void ShaderProgram::linkCheckErrors()
{
    int success, length;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char info_log[length];
        glGetProgramInfoLog(program, length, nullptr, info_log);
        std::cout << "ERROR::SHADER::LINKING_FAILED" << std::endl
                  << info_log << std::endl;
    }
}