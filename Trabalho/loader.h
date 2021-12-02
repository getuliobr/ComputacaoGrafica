#include "structures.h"
#pragma once

typedef struct {
  vector* vertices;
  vector* normals;
  vector* uvs;
} Object;

Object* loadOBJ(const char * path, bool* result);
void freeOBJ(Object* obj);