#include "box2d/box2d.h"
#include "physics.h"
#include "renderer.h"
#include "shader.h"
#include <window.h>
#include <game.h>
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>
#include <camera.h>

#define HEIGHT 800
#define WIDTH 600

// matrices for the shader
mat4 projection;
mat4 view;

// box2d, temporary
b2WorldId worldID;
b2BodyId bodyID;

// structs
struct Camera camera;

// callbacks
static inline void ShouldCloseChecker(GLFWwindow** window);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
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

    // Create the camera
    camera = C_CreateCamera(camera,(vec2){0.0,0.0});
    C_GetProjMatrix(camera, HEIGHT, HEIGHT, projection);
    C_GetViewMatrix(camera, view);

    // textures
    struct Texture Wall = T_LoadTextureFromFile(Wall, "../blocks.png", false);
    struct Texture Block = T_LoadAtlas(&Wall, 16, 0, 10);
    struct Texture Ground = T_LoadAtlas(&Wall, 16, 8, 9);

    // create the buffers
    unsigned int VAO = CreateVAO(VAO);
    unsigned int VBO = CreateVBO(VBO);
    unsigned int EBO = CreateEBO(EBO);

    // initialize world
    worldID = initPWorld(worldID, -400);

    // make physics objects for the opengl objects
    bodyID = initRect(worldID,300,300,200.0f,200.0f, true);
    b2BodyId box = initRect(worldID, 400, -100,600 , 1000, false);

    BindVAO(VAO);
    BindVBO(VBO);

    // bind texture
    T_Bind(Wall);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

// main loop
while (game.running) {
    // initializes the box2d physics world then steps it
    UpdatePWorld(worldID, 1.0f/60.0f, 4.0f);

    // check if the window should close
    ShouldCloseChecker(&window);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.41f, 0.65f, 0.90f, 1.0f);

    // Bind and configure the shader
    BindShader(shader);
    Shader_SetMat4(shader, "projection", projection);
    Shader_SetMat4(shader, "view", view);

    // Render the rectangles
    BindVAO(VAO);
    Renderer_FillRect(200, 200, Block,shader, VAO, VBO, EBO, bodyID);
    Renderer_FillRect(600, 1000, Ground,shader, VAO, VBO, EBO, box);

    // enable DebugDraw
    DebugDraw(worldID);

    // swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}


    // delete shader and shutdown the window
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

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    b2Vec2 velocity = b2Body_GetLinearVelocity(bodyID);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        game.running = false;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
         velocity.x = 150.0f;
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
         velocity.x = -150.0f;
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
         velocity.y = 300.0f;
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
         velocity.y = -150.0f;
    else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
        b2Body_SetAngularVelocity(bodyID,-2);
    b2Body_SetLinearVelocity(bodyID, velocity);
}

void framebuffersize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



