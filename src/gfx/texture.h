#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <stdbool.h>

struct Texture{
    GLuint ID;
    int width, height, nrChannels;
    float u_min, v_min, u_max,v_max;
};

struct Texture T_LoadTextureFromFile(struct Texture self, const char* path, bool flip);
struct Texture T_LoadAtlas(struct Texture self, int GridX, int GridY, int Posx, int Posy);
void T_Bind(struct Texture self);
void T_UnBindA();
void T_DeleteTex(struct Texture self);
void T_DeleteATex();
