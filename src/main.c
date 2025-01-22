#include "shader.h"
#include <stdio.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdlib.h>
#include <window.h>
#include <game.h>
#include <VAO.h>
#include <VBO.h>

#define HEIGHT 800
#define WIDTH 600

static inline void ShouldCloseChecker(GLFWwindow** window);

int main(int argc, const char* argv[])
{
    GLFWwindow* window;
    struct VertexAttr attributes[] = {
        {0, "position"},
        {1, "color"},
    };

    // Initialize window
    init_window(&window, WIDTH, HEIGHT, "Breakout");

    // Create shader
    struct Shader shader = CreateShader(
        "../vertex_shader.glsl",
        "../fragment_shader.glsl",
        2,
        attributes
    );
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };
    unsigned int VAO = CreateVAO(VAO);

    unsigned int VBO = CreateVBO(VBO);
    glGenVertexArrays(1, &VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    BindVAO(VAO);

    BindVBO(VBO);
    BufferVBO(sizeof(vertices), vertices);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    UnBindVAO();

    UnBindVBO();
    while (game.running) {
        ShouldCloseChecker(&window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        BindShader(shader);
        BindVAO(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    DeleteShader(shader);
    Shutdown_Window(&window);

    return 0;
}


static inline void ShouldCloseChecker(GLFWwindow** window)
{
     if (glfwWindowShouldClose(*window)){
         game.running = false;
     }
}

