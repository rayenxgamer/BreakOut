#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include <renderer.h>


void Renderer_InitRect(float x, float y, float height, float width,struct Texture self, unsigned int VAO, unsigned int VBO,unsigned int EBO){
    float uvX1 = 0.0f; float uvX2 = 0.0f;float uvY1 = 0.0f;float uvY2 = 0.0f;
    if (self.isAtlas) {
        uvX1 = self.uvX/self.width;
        uvX2 = (self.uvX - self.GridSize)/self.width;
        uvY1 = self.uvY/self.height;
        uvY2 = (self.uvY + self.GridSize)/self.height;
    }else {
        uvX1 = 0.0f; uvX2 = 1.0f;
        uvY1 = 0.0f; uvY2 = 1.0f;
    }
    float RectVertices[] = {
         x,  y + height,         0.0f, uvX2,uvY1,  // top right
         x, y,                   0.0f, uvX2,uvY2,  // bottom right
         x + width, y,           0.0f, uvX1,uvY2,  // bottom left
         x + width,  y + height, 0.0f, uvX1,uvY1   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    BindVAO(VAO);

    BindVBO(VBO);
    BufferVBO(sizeof(RectVertices), RectVertices);

    BindEBO(EBO);
    BufferEBO(sizeof(indices), indices);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}
