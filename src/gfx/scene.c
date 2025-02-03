#include "box2d/id.h"
#include "physics.h"
#include <scene.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node{
    b2BodyId BodyID;
    struct Node* next;
};
typedef struct Node n_Objects;

n_Objects* Create_New_Object(b2BodyId BodyID){
    n_Objects* result = malloc(sizeof(n_Objects));
    result->BodyID = BodyID;
    result->next = NULL;
    return result;
}

void SpawnBlocks(const char Level[7][7], b2WorldId worldId){
    n_Objects* head = NULL;
    n_Objects* temp;

    // i is maxed at 6 so its 7
    // same for j
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j<7; j ++) {
            printf("j is %d\n",j);
            printf("i is %d\n",i);
            switch (Level[i][j]) {
                case '0':
                printf("what does air taste like\n");
                case '1':
                printf("this is a wall \n");
                b2BodyId Wall = initRect(worldId, j, i, 100, 100, false);
                temp = Create_New_Object(Wall);
                temp->next = head;
                head = temp;
                case '2':
                printf("this is the breakable block\n");
                b2BodyId tile = initRect(worldId, j, i, 100, 100, false);
                temp = Create_New_Object(tile);
                temp->next = head;
                head = temp;
                case '9':
                printf("this is a death plane \n");
                default:
                break;
            }
        }
    }
}


