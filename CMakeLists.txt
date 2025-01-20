cmake_minimum_required(VERSION 3.30)
project(Breakout)

set(CMAKE_C_STANDARD)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Breakout
    src/main.c
    src/glad.c
    src/gfx/window.c
    src/gfx/game.c
    src/gfx/shader.c
)

target_include_directories(Breakout PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gfx
)

target_link_directories(Breakout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/libglfw3.a)

target_link_libraries(Breakout PRIVATE
    glfw
    m
    dl
    pthread
)
