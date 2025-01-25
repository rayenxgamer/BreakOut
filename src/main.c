#include "renderer.h"
#include "shader.h"
#include <stdio.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdlib.h>
#include <window.h>
#include <game.h>
#include <VAO.h>
#include <VBO.h>
#include <texture.h>

#define HEIGHT 800
#define WIDTH 600
float X = -0.5f;
float Y = -0.5f;


float uvX, uvY;
float x = 96.0f;
float y = 48.0f;
float GridSize = 16.0f;

static inline void ShouldCloseChecker(GLFWwindow** window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, const char* argv[])
{
    GLFWwindow* window;
    struct VertexAttr attributes[] = {
        {0, "position"},
        {1, "color"},
    };
    // Initialize window
    init_window(&window, WIDTH, HEIGHT, "Breakout");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetKeyCallback(window, key_callback);

    // Create shader
    struct Shader shader = CreateShader(
        "../vertex_shader.glsl",
        "../fragment_shader.glsl",
        2,
        attributes
    );
    struct Texture Wall = T_LoadTextureFromFile(Wall, "../blocks.png", false);
    unsigned int VAO = CreateVAO(VAO);

    unsigned int VBO = CreateVBO(VBO);
    unsigned int EBO;
    glGenBuffers(1,&EBO);
    BindVAO(VAO);
    BindVBO(VBO);
    T_Bind(Wall);


    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // color attribute
    while (game.running) {
        ShouldCloseChecker(&window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        BindShader(shader);
        BindVAO(VAO);
        uvX = x;
        uvY = y;
        Renderer_InitRect(X, Y,0.8f,0.6f, uvX/Wall.width, (uvX-GridSize)/Wall.width,(uvY+GridSize)/Wall.height,uvY/Wall.height, VAO, VBO, EBO);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        game.running = false;
    if (key == GLFW_KEY_D && action == GLFW_PRESS){
         X += 0.1f;
         x += GridSize;}
    else if (key == GLFW_KEY_A && action == GLFW_PRESS){
         X -= 0.1f;
         x -= GridSize;}
    else if (key == GLFW_KEY_W && action == GLFW_PRESS){
         Y += 0.1f;
         y += GridSize;}
    else if (key == GLFW_KEY_S && action == GLFW_PRESS){
         Y -= 0.1f;
         y -= GridSize;}
}



