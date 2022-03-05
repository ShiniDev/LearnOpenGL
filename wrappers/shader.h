#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    Shader(const std::string &, GLenum);

    GLuint &getShader() { return shader; }
    const GLuint &getShader() const { return shader; }

private:
    GLuint shader;
    const char *shaderSource;

    void compileCheckErrors();
};

#endif