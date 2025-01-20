#include <stdlib.h>
#include <window.h>
#include <game.h>


void init_window(GLFWwindow** window, int height, int width, const char* title)
{
    // Initializing GLFW
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    // Setting the OpenGL window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Creating the window
    *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!*window) {
        glfwTerminate();
        printf("Failed to create the window");
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(*window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize OpenGL context\n");
        exit(EXIT_FAILURE);
    }

    game.running = true;
}

void Shutdown_Window(GLFWwindow** window){
    glfwDestroyWindow(*window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

