#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

vec3* create_vec3(int size) {
  return (vec3*) calloc(size, sizeof(vec3));
}

vector* create_vector(int size) {
  if(size < 1) {
    printf("Error: size must be greater than 0\n");
    return NULL;
  }
  vector* v = (vector*) calloc(1, sizeof(vector));
  v->size = size;
  v->curr = 0;
  v->vector = create_vec3(size);
  return v;   
}

void push_back(vector* v, vec3 v3) {
  if(v->size == v->curr) {
    v->size *= 2;
    v->vector = (vec3*) realloc(v->vector, v->size * sizeof(vec3));
  }
  v->vector[v->curr++] = v3;    
}

void free_vector(vector* v) {
  free(v->vector);
  free(v);
}