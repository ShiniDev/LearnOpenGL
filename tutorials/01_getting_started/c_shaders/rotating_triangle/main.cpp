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

void rotate(float *x, float *y, int angle)
{
    float o_x = *x;
    float o_y = *x;
    *x = o_x * cos(angle) - o_y * sin(angle);
    *y = o_x * sin(angle) + o_y * cos(angle);
}

void process_input(GLFWwindow *window, float *angle, float delta_time)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        *angle += (1 * delta_time);
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        *angle -= (1 * delta_time);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rotating Triangle", nullptr, nullptr);
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
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        //
    };

    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::string vs_s = my_utils::read_f(my_utils::get_exec_dir() + "triangle.vs.glsl");
    std::string fs_s = my_utils::read_f(my_utils::get_exec_dir() + "triangle.fs.glsl");

    Shader vs{vs_s, GL_VERTEX_SHADER};
    Shader fs{fs_s, GL_FRAGMENT_SHADER};
    ShaderProgram s_prog{{vs.getShader(), fs.getShader()}};

    vs.deleteShader();
    fs.deleteShader();

    float angle = 0;
    float last_time = glfwGetTime();
    int angle_uniform_loc = s_prog.uniformLoc("angle");

    while (!glfwWindowShouldClose(window)) {
        float current_time = glfwGetTime();
        float delta_time = (current_time - last_time) / 1000.0f;

        // process_input(window, &angle, delta_time);
        my_utils::process_input(window);

        glClearColor(1.0f, 0.5f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        s_prog.useProgram();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUniform1f(angle_uniform_loc, angle);

        angle += (200 * delta_time);

        last_time = current_time;

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}