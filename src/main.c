#include "EBO.h"
#include "cglm/affine2d.h"
#include "cglm/util.h"
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
#include <camera.h>

#define HEIGHT 800
#define WIDTH 600
float X = 200;
float Y = 400;

mat4 projection;
mat4 view;
mat4 model;
struct Camera camera;
static inline void ShouldCloseChecker(GLFWwindow** window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffersize_callback(GLFWwindow* window, int width, int height);

int main(int argc, const char* argv[])
{
    GLFWwindow* window;
    struct VertexAttr attributes[] = {
        {0, "position"},
        {1, "texture"},
    };
    // Initialize window
    init_window(&window, WIDTH, HEIGHT, "Breakout");
    glfwSetFramebufferSizeCallback(window, framebuffersize_callback);
    glfwSetKeyCallback(window, key_callback);
    // Create shader
    struct Shader shader = CreateShader(
        "../vertex_shader.glsl",
        "../fragment_shader.glsl",
        2,
        attributes
    );
    vec2 pos = {0,0};
    camera = C_CreateCamera(camera,pos);
    C_GetProjMatrix(camera, HEIGHT, HEIGHT, projection);
    C_GetViewMatrix(camera, view);
    glm_mat4_identity(model);
    struct Texture Wall = T_LoadTextureFromFile(Wall, "../blocks.png", false);
    struct Texture Lava1 = T_LoadAtlas(&Wall, 16, 7, 0);
    unsigned int VAO = CreateVAO(VAO);

    unsigned int VBO = CreateVBO(VBO);
    unsigned int EBO = CreateEBO(EBO);
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
        Shader_SetMat4(shader, "projection", projection);
        Shader_SetMat4(shader, "view", view);
        Shader_SetMat4(shader, "model", model);
        printf("%f\n",X);
        printf("%f\n",Y);
        BindVAO(VAO);
        Renderer_InitRect(X, Y,100,200,Lava1, VAO, VBO, EBO);
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
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
         X += 20.0f;
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
         X -= 20.0f;
    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
         Y += 20.0f;
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
         Y -= 20.0f;
}

void framebuffersize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



