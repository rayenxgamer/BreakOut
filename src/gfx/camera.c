#include <camera.h>
#include <string.h>


struct Camera C_CreateCamera(struct Camera self, vec2 pos){
    memcpy(self.pos, pos, sizeof(vec2));
    return self;
}
void C_GetViewMatrix(struct Camera self, mat4 dest){
    mat4 identity;
    glm_mat4_identity(identity);
    glm_translate(identity,(vec3){-self.pos[0],-self.pos[1] , 0.0f});
    glm_mat4_copy(identity, dest);
}

void C_GetProjMatrix(struct Camera self,float height,float width, mat4 dest){
    mat4 identity;
    glm_mat4_identity(identity);
    glm_ortho(0, width, 0, height, -1, 1, identity);
    memcpy(dest, identity, sizeof(mat4));
}

struct Camera C_Move(struct Camera self, float x, float y){
    self.pos[0] += x;
    self.pos[1] += y;
    return self;
}
