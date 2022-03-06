#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <my_utils.h>
#include <shader.h>
#include <shader_program.h>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Diamond", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, my_utils::framebuffer_size_callback);

    std::vector<float> vertices{
        -0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        //
    };

    std::vector<unsigned int> indices{
        0, 1, 2,
        0, 3, 4,
        4, 5, 6,
        6, 7, 2
        //
    };

    GLuint vbo, ebo, vao;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // Vertices data to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    // Indices data to GL_ELEMENT_ARRAY_BUFFER
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind GL_ELEMENT_ARRAY_BUFFER after unbinding vertex array
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::string vs_source = my_utils::read_f(my_utils::get_exec_dir() + "diamond.vs.glsl");
    std::string fs_source = my_utils::read_f(my_utils::get_exec_dir() + "diamond.fs.glsl");
    // Vertex
    Shader vs{vs_source, GL_VERTEX_SHADER};
    // Fragment
    Shader fs{fs_source, GL_FRAGMENT_SHADER};
    ShaderProgram prog{{vs.getShader(), fs.getShader()}};

    vs.deleteShader();
    fs.deleteShader();

    while (!glfwWindowShouldClose(window)) {
        my_utils::process_input(window);

        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        prog.useProgram();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    prog.deleteProgram();

    glfwTerminate();
    return 0;
}