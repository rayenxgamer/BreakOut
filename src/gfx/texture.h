#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <stdbool.h>

struct Texture{
    GLuint ID;
    int width, height, nrChannels;
    float uvX,uvY;
    float GridSize;
    bool isAtlas;
};

struct Texture T_LoadTextureFromFile(struct Texture self, const char* path, bool flip);
struct Texture T_LoadAtlas(struct Texture* self,float GridSize, float GridX, float GridY);
void T_Bind(struct Texture self);
void T_UnBindA();
void T_DeleteTex(struct Texture self);
void T_DeleteATex();
