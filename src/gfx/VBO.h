#pragma once

#include <glad/glad.h>

GLuint CreateVBO(unsigned int VBO);
void BindVBO(unsigned int VBO);
void BufferVBO(GLsizeiptr size, const GLvoid *data);
void UnBindVBO();
