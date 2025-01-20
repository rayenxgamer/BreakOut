#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <glad/glad.h>

struct VertexAttr{
    GLuint index;
    const GLchar* name;
};

struct Shader{
    GLuint handle,vs_handle,fs_handle;
};

GLint ReadAndCompile(const char* path, GLenum type);

struct Shader CreateShader(const char* vs_path,const char* fs_path, size_t n,struct VertexAttr attributes[]);

void DeleteShader(struct Shader self);

void BindShader(struct Shader self);
