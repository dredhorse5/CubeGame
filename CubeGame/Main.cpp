//#include <SOIL.h>
#include <glut.h>
#include <iostream>

float x = 0;

void changeSize(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	///////////////// THE KOSTYA IS SLEEPING /////////////////////////
}
///////////////////////////////
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	x += 0.5;
	glRotatef(x, 1, 0, 0);

	
	glBegin(GL_QUADS);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
	
	if (x > 180) x = 0;
	glutPostRedisplay();
	glPopMatrix();
	glFinish();
	glutSwapBuffers();
	
}
// // create//////////////
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Óðîê 1");

	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 1;
}