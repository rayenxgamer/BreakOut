#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <cglm/cglm.h>
#include <glad/glad.h>

struct VertexAttr{
    GLuint index;
    const GLchar* name;
};

struct Shader{
    GLuint handle,vs_handle,fs_handle;
};

static GLint ReadAndCompile(const char* path, GLenum type);

struct Shader CreateShader(const char* vs_path,const char* fs_path, size_t n,struct VertexAttr attributes[]);

void DeleteShader(struct Shader self);

void BindShader(struct Shader self);

void Shader_SetFloat(struct Shader self,const char* name, GLfloat value);
void Shader_SetBool(struct Shader self, const char* name, bool value);
void Shader_SetInt(struct Shader self, const char* name, GLint value);
void Shader_SetMat4(struct Shader self, const char* name, mat4 value);
void Shader_SetVec3(struct Shader self, const char* name, vec3 value);
