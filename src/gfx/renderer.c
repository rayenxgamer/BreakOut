#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <renderer.h>


void Renderer_InitRect(float x, float y, float height, float width,float uvX1, float uvX2,float uvY1, float uvY2, unsigned int VAO, unsigned int VBO,unsigned int EBO){

    float RectVertices[] = {
         x,  y + height,         0.0f, uvX2,uvY2,  // top right
         x, y,                   0.0f, uvX2,uvY1,  // bottom right
         x + width, y,           0.0f, uvX1,uvY1,  // bottom left
         x + width,  y + height, 0.0f, uvX1,uvY2   // top left
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
