#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

struct Texture{
    GLuint ID;
    int width, height, nrChannels;
};

struct Texture T_LoadTextureFromFile(struct Texture self, const char* path);
void T_Bind(struct Texture self);
void T_UnBindA();
void T_DeleteTex(struct Texture self);
void T_DeleteATex();
