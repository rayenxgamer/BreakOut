#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "box2d/id.h"
#include "shader.h"
#include <cglm/cglm.h>
#include <renderer.h>


// fill the rectangle that was created by using InitRect,
// will automatically get assigned the position of the passed body (messy asf)

void Renderer_FillRect(float height, float width, struct Texture self,struct Shader shader,
                       unsigned int VAO, unsigned int VBO, unsigned int EBO, b2BodyId body) {
    mat4 model;
    float uvX1 = 0.0f, uvX2 = 0.0f, uvY1 = 0.0f, uvY2 = 0.0f;
    // gets the physics objects's  position and rotation
    b2Vec2 position = b2Body_GetPosition(body);
    float rotationAngle = b2Rot_GetAngle(b2Body_GetRotation(body)); // Rotation angle in radians

    glm_mat4_identity(model); // Reset the model matrix
    glm_translate(model, (vec3){position.x, position.y, 0.0f}); // Translate to the Box2D body's position
    glm_rotate(model, rotationAngle, (vec3){0.0f, 0.0f, 1.0f}); // Rotate around the Z-axis
    Shader_SetMat4(shader, "model", model);

    // checks if its an atlas then if it is then work out the uv's
    // otherwise use the whole texture

    if (self.isAtlas) {
        uvX1 = self.uvX / self.width;
        uvX2 = (self.uvX + self.GridSize) / self.width;
        uvY1 = self.uvY / self.height;
        uvY2 = (self.uvY + self.GridSize) / self.height;
    } else {
        uvX1 = 0.0f; uvX2 = 1.0f;
        uvY1 = 0.0f; uvY2 = 1.0f;
    }

    // Center the rectangle around (0, 0)
    float RectVertices[] = {
        -width / 2.0f,  height / 2.0f, 0.0f, uvX1, uvY1,  // top left
        -width / 2.0f, -height / 2.0f, 0.0f, uvX1, uvY2,  // bottom left
         width / 2.0f, -height / 2.0f, 0.0f, uvX2, uvY2,  // bottom right
         width / 2.0f,  height / 2.0f, 0.0f, uvX2, uvY1   // top right
    };

    unsigned int indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    BindVAO(VAO);
    BindVBO(VBO);
    BufferVBO(sizeof(RectVertices), RectVertices);

    BindEBO(EBO);
    BufferEBO(sizeof(indices), indices);

    // draw call
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // reset the model matrix
    glm_mat4_identity(model); // Reset the model matrix
    Shader_SetMat4(shader, "model", model);
}

