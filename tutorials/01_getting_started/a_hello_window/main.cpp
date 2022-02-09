#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  float red, green, blue;
  red = 1.0f;
  green = 0.5f;
  blue = 0.0f;
  bool redInc, greenInc, blueInc;
  redInc = false;
  greenInc = false;
  blueInc = true;
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    glClearColor(red, green, blue, 1.0f);
    // glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (red > 0.01f && !redInc)
    {
      red -= 0.01f;
    }
    else if (red < 0.99f)
    {
      red += 0.01f;
      redInc = true;
    }
    else
    {
      redInc = false;
    }
    if (green > 0.01f && !greenInc)
    {
      green -= 0.01f;
    }
    else if (green < 0.99f)
    {
      green += 0.01f;
      greenInc = true;
    }
    else
    {
      greenInc = false;
    }
    if (blue > 0.01f && !blueInc)
    {
      blue -= 0.01f;
    }
    else if (blue < 0.99f)
    {
      blue += 0.01f;
      blueInc = true;
    }
    else
    {
      blueInc = false;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}