#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "shader.h"
using namespace std;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    float coords[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int buffer;
    // Create buffer
    glGenBuffers(1, &buffer);
    // "Select" buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // Set buffer data
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), coords, GL_DYNAMIC_DRAW);
    // Gives OpenGL context on buffer data
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    // Enables buffer
    glEnableVertexAttribArray(0);

    ShaderSource ssource("res/shaders.shader");
    glUseProgram(ssource.createShader());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
