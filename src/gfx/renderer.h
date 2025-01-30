#pragma once
#include "box2d/id.h"
#include "shader.h"
#include <texture.h>
#include <box2d/box2d.h>

void Renderer_FillRect(float height, float width, struct Texture self,struct Shader shader,
                       unsigned int VAO, unsigned int VBO, unsigned int EBO, b2BodyId body);
