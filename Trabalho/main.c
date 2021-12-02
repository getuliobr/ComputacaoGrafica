#include <GL/glut.h>
#include <stdio.h>
#include <windows.h>
#include "structures.h"
#include "loader.h"

Object* obj;
bool res;

float globalEyeX = 0;
float globalEyeY = 0;
float globalEyeZ = 0;

int init(void){
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //define a cor de fundo
  glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
}

int spin = 0;

int FPS = 60;

void loop(int v) {
  spin += 1;
  glutPostRedisplay();

  glutTimerFunc(1000/FPS, loop, 0);
}

void drawObject(Object* obj) {
  glPushMatrix();

  glViewport(0, 0, 800, 800);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, 1, 1, 500);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(globalEyeX, 5, globalEyeZ,
            0, 0, 0,
            0, 1, 0);

  glRotatef(-90, 1, 0, 0);
  glRotatef(spin, 0, 0, 1);
  glBegin(GL_TRIANGLES);
  for(int i = 0; i < obj->vertices->curr && res == true; i += 1) {
    vec3 v = obj->vertices->vector[i];
    vec3 n = obj->normals->vector[i];
    vec3 u = obj->uvs->vector[i];
    glNormal3f(n.x, n.y, n.z);
    glTexCoord2f(u.x, u.y);
    glVertex3f(v.x, v.y, v.z);
  }
  glEnd();

  glPopMatrix();
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0f, 0.0f, 0.0f);

  drawObject(obj);

  glFlush();
}

void specialKey(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      globalEyeX += 1;
      break;
    case GLUT_KEY_DOWN:
      globalEyeX -= 1;
      break;
    case GLUT_KEY_LEFT:
      globalEyeZ -= 1;
      
      break;
    case GLUT_KEY_RIGHT:
      globalEyeZ += 1;
      
      break;
    default:
      return;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Trabalho");

  if(argc == 2) {
    obj = loadOBJ(argv[1], &res);

    init();
    
    glutSpecialFunc(specialKey);
    glutDisplayFunc(display);
    glutTimerFunc(1, loop, 0);

    glutMainLoop();
  } else {
    printf("Usage: %s <filename>\n", argv[0]);
  }
  return 0;
}
