#pragma once

typedef struct {
  float x, y, z;
} vec3;

typedef struct {
  vec3* vector;
  int curr;
  int size;
} vector;

typedef enum { true, false } bool;

vec3* create_vec3(int size);
vector* create_vector(int size);
void push_back(vector* v, vec3 v3);
void free_vector(vector* v);