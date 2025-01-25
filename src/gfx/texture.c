#include "shader.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <texture.h>

struct Texture T_LoadTextureFromFile(struct Texture self, const char* path, bool flip){
    glGenTextures(1,&self.ID);
    glBindTexture(GL_TEXTURE_2D, self.ID);
    // paramamamamamother

    if (flip) {
        stbi_set_flip_vertically_on_load(true);
    }else{
        stbi_set_flip_vertically_on_load(false);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // allocate data for the image
    u_char* image = stbi_load(path, &self.width, &self.height, &self.nrChannels, 0);
    if (image)
    {
        printf("loading texture\n");
        // flip texture
        // a switch to check for the number of channels then generates the texture
        switch (self.nrChannels) {
            case 1:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, self.width, self.height, 0, GL_RED, GL_UNSIGNED_BYTE, image);
            case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, self.width, self.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self.width, self.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        printf("texture loaded!\n");
    }else{
        printf("Failed to load texture at: %s\n", path);
    }

    // free data
    stbi_image_free(image);

    // unbind after generating, unsure if this will cause problems since im gonna write a bind function anyways
    glBindTexture(GL_TEXTURE_2D, 0);

    return self;
}

struct Texture T_LoadAtlas(struct Texture* self,float GridSize, float GridX, float GridY){
    self -> GridSize = GridSize;
    float i = 0.0f;
    float j = 0.0f;
    if (GridX == 0){
        GridX++;
        if (GridY != 0) {
            GridY --;
        }
    }
    GridX = GridX * GridSize;
    GridY = GridY * GridSize;
    while (i<GridX) {
        i+=GridSize;
    }
    while (j<GridY) {
        j+=GridSize;
    }
    self ->uvX = i;
    self ->uvY = j;
    printf("%f\n", i);
    printf("%f\n", j);
    return *self;
}

void T_Bind(struct Texture self){
    glBindTexture(GL_TEXTURE_2D, self.ID);
    printf("Texture Bound!\n");
}

void T_UnBindA(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void T_DeleteTex(struct Texture self){
        glDeleteTextures(1, &self.ID);
}

void T_DeleteATex(){
        glDeleteTextures;
}
