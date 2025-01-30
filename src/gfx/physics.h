#pragma once

#include "box2d/id.h"
#include <glad/glad.h>
#include <box2d/box2d.h>
#include <box2d/types.h>

struct World{
   b2Vec2 gravity;
};

// initialize the physics world (done before doing or creating any physics object)
b2WorldId initPWorld(b2WorldId self, float gravity);


b2BodyId initRect(b2WorldId worldID,
                          float x, float y, float height, float width, bool dyn);

void DebugDraw(b2WorldId worldID);
// updating the world, should be put in the game loop
void UpdatePWorld(b2WorldId self, float timestep, int substep);
