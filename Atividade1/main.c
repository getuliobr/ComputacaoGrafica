#include <GL/glut.h>
#include <stdio.h>

int tx = 0;
int ty = 0;

int cx = 5;
int cy = 5;

void drawSquare() {
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2i(0, 0);
  glVertex2i(10, 0);
  glVertex2i(10, 10);
  glVertex2i(0, 10);
  glEnd();
}

int init(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(cx, cy, 0);             // Move para a posicao inicial
  glScalef(1.25,1.25,1.0);             // Escala
  glTranslatef(-cx, -cy, 0);           // Move de volta

  drawSquare();
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
