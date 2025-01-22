#include <VAO.h>


void CreateVAO(unsigned int VAO){
    glGenVertexArrays(1,&VAO);
}


void BindVAO(unsigned int VAO){
    glBindVertexArray(VAO);
}

void UnBindVAO(){
    glBindVertexArray(0);
}

