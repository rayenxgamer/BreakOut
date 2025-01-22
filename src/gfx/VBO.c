#include <VBO.h>

GLuint CreateVBO(unsigned int VBO){
    glGenBuffers(1,&VBO);
    return VBO;
}

void BindVBO(unsigned int VBO){
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
}


// ill add an option to change from GL_STATIC_DRAW to other stuff
// if i need it
void BufferVBO(GLsizeiptr size, const GLvoid *data){
    glBufferData(GL_ARRAY_BUFFER, size, data,GL_DYNAMIC_DRAW);
}

void UnBindVBO(){
    glBindVertexArray(0);
}

