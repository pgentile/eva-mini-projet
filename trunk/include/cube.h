#ifndef CUBE_H
#define CUBE_H

#define MAX_VERTICES 100
#define MAX_FACES    50

typedef struct {
  float x,y,z;//space coords
  
} vertex_t;

typedef struct {
  int a,b,c;
  
  float x,y,z;
} face_t;

vertex_t cube_vertices[MAX_VERTICES]={
  { -1, -1, 1},   // vertex v0
  {1,  -1, 1},   // vertex v1
  {1,  -1, -1},  // vertex v2
  { -1, -1, -1},  // vertex v3
  { -1, 1,  1},   // vertex v4
  { 1,  1,  1},   // vertex v5
  { 1,  1,  -1},  // vertex v6 
  {-1, 1,  -1},   // vertex v7
};

face_t  cube_faces[MAX_FACES]={
  {0, 1, 4},{0,0,1},  // polygon v0,v1,v4
  {1, 5, 4},{0,0,1},  // polygon v1,v5,v4
  {1, 2, 5},{1,0,0},  // polygon v1,v2,v5
  {2, 6, 5},{1,0,0},  // polygon v2,v6,v5
  {2, 3, 6},{0,0,-1},  // polygon v2,v3,v6
  {3, 7, 6},{0,0,-1},  // polygon v3,v7,v6
  {3, 0, 7},{-1,0,0},  // polygon v3,v0,v7
  {0, 4, 7},{-1,0,0},  // polygon v0,v4,v7
  {4, 5, 7},{0,1,0},  // polygon v4,v5,v7
  {5, 6, 7},{0,1,0},  // polygon v5,v6,v7
  {3, 2, 0},{0,-1,0},  // polygon v3,v2,v0
  {2, 1, 0},{0,-1,0} // polygon v2,v1,v0
};


#endif
