#include <GL/glut.h>
#include <stdio.h>

int init(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0,100.0,0.0,100.0);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void specialKey(int key, int x, int y) {
  printf("Pressed special: %d\n", key);
}

void normalKey(unsigned char key, int x, int y) {
  printf("Pressed normal: %c\n", key);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Atividade 1");

  init();
  glutSpecialFunc(specialKey);
  glutKeyboardFunc(normalKey);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
