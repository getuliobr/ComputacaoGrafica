#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"

#define MIN_VEC_SIZE 10000

bool loadOBJ(const char * path, vector* out_vertices, vector* out_uvs, vector* out_normals) {
  FILE * file = fopen(path, "r");

  vector* vertexUvNormalIndices = create_vector(MIN_VEC_SIZE);

  vector* temp_vertices = create_vector(MIN_VEC_SIZE);
  vector* temp_uvs = create_vector(MIN_VEC_SIZE);
  vector* temp_normals = create_vector(MIN_VEC_SIZE);

  if( file == NULL ){
    printf("Impossible to open the file !\n");
    return false;
  }
  while( 1 ){

    char lineHeader[128];
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
      break;

    if ( strcmp( lineHeader, "v" ) == 0 ) {
      vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
      push_back(temp_vertices, vertex);
    }else if ( strcmp( lineHeader, "vt" ) == 0 ) {
      vec3 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y );
      push_back(temp_uvs, uv);
    }else if ( strcmp( lineHeader, "vn" ) == 0 ) {
      vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
      push_back(temp_normals, normal);
    }else if ( strcmp( lineHeader, "f" ) == 0 ) {
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
      if (matches != 9){
        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
        return false;
      }
      vec3 vun0 = {vertexIndex[0], uvIndex[0], normalIndex[0]};
      push_back(vertexUvNormalIndices, vun0);

      vec3 vun1 = {vertexIndex[1], uvIndex[1], normalIndex[1]};
      push_back(vertexUvNormalIndices, vun1);

      vec3 vun2 = {vertexIndex[2], uvIndex[2], normalIndex[2]};
      push_back(vertexUvNormalIndices, vun2);
    }

  }

  for( unsigned int i=0; i < vertexUvNormalIndices->curr; i++ ) {
    int vertexIndex = vertexUvNormalIndices->vector[i].x;
    vec3 vertex = temp_vertices->vector[vertexIndex-1];
    push_back(out_vertices, vertex);

    int uvIndex = vertexUvNormalIndices->vector[i].y;
    vertex = temp_uvs->vector[uvIndex-1];
    push_back(out_uvs, vertex);

    int normalIndex = vertexUvNormalIndices->vector[i].z;
    vertex = temp_normals->vector[normalIndex-1];
    push_back(out_normals, vertex);
  }

  free_vector(vertexUvNormalIndices);
  free_vector(temp_vertices);
  free_vector(temp_uvs);
  free_vector(temp_normals);

  return true;
}