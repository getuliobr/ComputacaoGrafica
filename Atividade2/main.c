#include <GL/glut.h>
#include <windows.h> 

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

typedef enum { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT } Position;

void bule(Position pos) {
  glPushMatrix();

  int x = pos == TOP_LEFT || pos == BOTTOM_LEFT ? 0 : 400;
  int y = pos == TOP_LEFT || pos == TOP_RIGHT ? 400 : 0;

  glViewport(x, y, 400, 400);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  pos != BOTTOM_RIGHT ? glOrtho(-3, 3, -3, 3, 1, 50) : gluPerspective(70, 1, 1, 50);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  float eyeX = 0;
  float eyeY = 0;
  float eyeZ = 0;
  float upX = 0;
  float upY = 0;
  float upZ = 0;

  switch (pos) {
    case TOP_LEFT:
      eyeY = 3;
      upY = -1;
      upZ = -1;
      break;
    
    case TOP_RIGHT:
      eyeX = -3;
      upY = 1;
      break;

    case BOTTOM_LEFT:
      eyeZ = 3;
      upY = 1;
      break;

    case BOTTOM_RIGHT:
      eyeZ = 5;
      upY = 1;
      break;

    default:
      break;
  }

  gluLookAt(eyeX, eyeY, eyeZ,
            0, 0, 0,
            upX, upY, upZ);

  if(pos == BOTTOM_RIGHT) {
    glRotatef(spin, 0, 0, 1);
    glRotatef(45, 1, 0, 0);
  }

  glutWireTeapot(2);
  glPopMatrix();
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0f, 0.0f, 0.0f);

  bule(TOP_LEFT);
  bule(TOP_RIGHT);
  bule(BOTTOM_LEFT);
  bule(BOTTOM_RIGHT);

  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Atividade 2");

  init();

  glutDisplayFunc(display);
  glutTimerFunc(1, loop, 0);

  glutMainLoop();
  return 0;
}
