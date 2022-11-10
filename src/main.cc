#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
using namespace std;

static unsigned int compileShader(unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(!result) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        char *message = (char*)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);

        cout << message;
        glDeleteShader(id);
        return 0;
    }

    return id;
} 

static unsigned int createShader(const string& vertexShader, const string& fragmentShader) {

    unsigned int program = glCreateProgram();
    unsigned int vShader = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return program;
}

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

    string vertexShader = 
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "void main() {\n"
        "   gl_Position = position;\n"
        "}\n";
        
    string fragmentShader = 
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "void main() {\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";
        
    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

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
