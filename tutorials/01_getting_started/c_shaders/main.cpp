#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <my_utils.h>
#include <shader.h>
#include <shader_program.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shaders", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create a GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
    glfwSetFramebufferSizeCallback(window, my_utils::framebuffer_size_callback);

    std::vector<float> vertices{
        // Vertices         // Colors
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        //
    };

    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::string vs_s = my_utils::read_f(my_utils::get_exec_dir() + "shaders.vs.glsl");
    std::string fs_s = my_utils::read_f(my_utils::get_exec_dir() + "shaders.fs.glsl");

    Shader vs{vs_s, GL_VERTEX_SHADER};
    Shader fs{fs_s, GL_FRAGMENT_SHADER};
    ShaderProgram s_prog{{vs.getShader(), fs.getShader()}};

    vs.deleteShader();
    fs.deleteShader();

    while (!glfwWindowShouldClose(window)) {
        my_utils::process_input(window);

        glClearColor(1.0f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        s_prog.useProgram();
        int x_offset_loc = s_prog.uniformLoc("xOffset");
        glUniform1f(x_offset_loc, cos(glfwGetTime()));
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    s_prog.deleteProgram();

    glfwTerminate();
    return 0;
}