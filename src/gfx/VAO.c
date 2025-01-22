#include <VAO.h>


GLuint CreateVAO(unsigned int VAO){
    glGenVertexArrays(1,&VAO);
    return VAO;
}


void BindVAO(unsigned int VAO){
    glBindVertexArray(VAO);
}

void UnBindVAO(){
    glBindVertexArray(0);
}

