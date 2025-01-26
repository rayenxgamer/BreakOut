#pragma once

#include "cglm/types.h"
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <shader.h>


struct Camera{
    vec2 pos;
};

// will create a camera at the position vec2 pos
struct Camera C_CreateCamera(struct Camera self, vec2 pos);
// sets the viewmatrix variable to mat4 dest
void C_GetViewMatrix(struct Camera self, mat4 dest);
// gets the projection matrix
void C_GetProjMatrix(struct Camera self,float height,float width, mat4 dest);
// moves the camera (theoretically) i suck at this))
struct Camera C_Move(struct Camera self, float x, float y);
