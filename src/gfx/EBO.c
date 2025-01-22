#include <EBO.h>

GLuint CreateEBO(unsigned int EBO){
    glGenBuffers(1,&EBO);
    return EBO;
}

void BufferEBO(GLsizeiptr size, const GLvoid *data){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size,data,GL_STATIC_DRAW);
}

void BindEBO(unsigned int EBO){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
}

void UnBindEBO(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

