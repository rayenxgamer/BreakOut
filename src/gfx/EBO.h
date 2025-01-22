#pragma once

#include <glad/glad.h>

GLuint CreateEBO(unsigned int EBO);
void BufferEBO(GLsizeiptr size, const GLvoid *data);
void BindEBO(unsigned int EBO);
void UnBindEBO();

