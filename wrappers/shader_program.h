#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <initializer_list>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderProgram
{
public:
    ShaderProgram(std::initializer_list<GLuint>);

    const GLuint &getProgram() const { return program; }
    GLuint &getProgram() { return program; }
    void useProgram() { glUseProgram(program); }
    void deleteProgram() { glDeleteProgram(program); }

private:
    GLuint program;

    void linkCheckErrors();
};

#endif