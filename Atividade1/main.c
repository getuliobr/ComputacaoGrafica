#include <GL/glut.h>

int init(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0,100.0,0.0,100.0);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Atividade 1");

  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
