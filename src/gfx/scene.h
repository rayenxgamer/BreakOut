#pragma once

#include <cglm/cglm.h>
#include <texture.h>
#include <shader.h>
#include <glad/glad.h>
#include <box2d/box2d.h>
#include <renderer.h>
#include <physics.h>


void SpawnBlocks(const char Level[7][7], b2WorldId worldId);
