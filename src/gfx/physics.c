#include "box2d/box2d.h"
#include "box2d/collision.h"
#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include <physics.h>
#include <stdio.h>


void DrawTransform(const b2Transform xf, void* context);
void DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context);
void DrawCircle(b2Vec2 center, float radius, const b2HexColor color, void* context);
void DrawSegment(b2Vec2 p1, b2Vec2 p2,  b2HexColor color, void* context);
void DrawAABB(b2AABB* aabb, const b2HexColor c);

// initialize the world
b2WorldId initPWorld(b2WorldId self, float gravity){
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, gravity};
    self = b2CreateWorld(&worldDef);
    return self;
}

// initialize a rectangle in the physics world so it can be filled with opengl later
b2BodyId initRect(b2WorldId worldID,
                          float PosX, float PosY, float height, float width, bool dyn){
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    if (dyn) {
        groundBodyDef.type = b2_dynamicBody;
    } else {
        groundBodyDef.type = b2_staticBody;
    }
    groundBodyDef.position = ConvertToGridPos(PosX, PosY);
    b2BodyId bodyID = b2CreateBody(worldID, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(width/2, height/2);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    if (dyn) {
        groundShapeDef.density = 1.0f ;
            groundShapeDef.friction = 0.3f ;
    }
    b2CreatePolygonShape(bodyID, &groundShapeDef, &groundBox);
    return bodyID;
}

b2Vec2 ConvertToGridPos(float x,float y){
    x = (x * 100) + 50;
    y = (y*100) + 50;
    return (b2Vec2){x,y};
}
// the function to enable debug drawing
void DebugDraw(b2WorldId worldID){
    b2DebugDraw debugdraw = b2DefaultDebugDraw();
    // Debug drawing for Box2D
    debugdraw.drawAABBs = true;
    debugdraw.drawShapes = true;
    debugdraw.DrawCircle = DrawCircle;
    debugdraw.DrawPolygon = DrawPolygon;

    b2World_Draw(worldID, &debugdraw);
}

// update the physics world
void UpdatePWorld(b2WorldId self, float timestep, int substep){
    b2World_Step(self, timestep, substep);
}



// rest is all the debug functions to be assigned to DebugDraw
void DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context)
{
    glColor4f(0, 1, 0, 0.5f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < vertexCount; i++) {
        b2Vec2 v = vertices[i];
        glVertex2f(v.x, v.y);
    }
    glEnd();
}

void DrawCircle(b2Vec2 center, float radius, const b2HexColor color, void* context) {
    const float k_segments = 16.0f;
    int vertexCount = 16;
    const float k_increment = 2.0f * 3.1415926535 / k_segments;
    float theta = 0.0f;

    glColor4f(1, 0, 0, 1);
    glBegin(GL_LINE_LOOP);
    GLfloat glVertices[vertexCount * 2];
    for (int i = 0; i < k_segments; ++i) {
        b2Vec2 v;
        v.x = center.x + radius * cos(theta);
        v.y = center.y + radius * sin(theta);
        glVertex2f(v.x, v.y);
        theta += k_increment;
    }
    glEnd();
}


void DrawAABB(b2AABB* aabb, const b2HexColor c) {
    glColor4f(1, 0.2, 0.4, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(aabb->lowerBound.x, aabb->lowerBound.y);
    glVertex2f(aabb->upperBound.x, aabb->lowerBound.y);
    glVertex2f(aabb->upperBound.x, aabb->upperBound.y);
    glVertex2f(aabb->lowerBound.x, aabb->upperBound.y);
    glEnd();
}
void DrawSegment(b2Vec2 p1, b2Vec2 p2,  b2HexColor color, void* context){
    glColor4f(0.2, 0.1, 0.2, 1);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}
void DrawTransform(const b2Transform xf, void* context) {
    b2Vec2 p1 = xf.p;
    b2Vec2 p2;
    const float k_axisScale = 0.4f;

    // Calculate the x-axis
    p2.x = p1.x + k_axisScale * xf.q.c;
    p2.y = p1.y + k_axisScale * xf.q.s;
    DrawSegment(p1, p2, b2_colorAliceBlue, context );

    // Calculate the y-axis
    p2.x = p1.x - k_axisScale * xf.q.s;
    p2.y = p1.y + k_axisScale * xf.q.c;
    DrawSegment(p1, p2, b2_colorAliceBlue, context);
}

