#include <iostream>
#include <glut.h>
#include <gl/GLU.h>

void display();
void reshape(int, int);
void timer(int);

void init()
{////
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500, 500);

	glutCreateWindow("Cube");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	init();
	//////////
	glutMainLoop();
}

float angle = 0.0;
//////////////////

glutKeyboardFunc(processNormalKeysDOWN);
glutKeyboardUpFunc(processNormalKeysUP);

void processNormalKeysDOWN(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
	case 'W':
		KeyFront = 1.0;
		break;
	case 's':
	case 'S':
		KeyFront = -1.0;
		break;
	case 'a':
	case 'A':
		KeySide = -1.0;
		break;
	case 'd':
	case 'D':
		KeySide = 1.0;
		break;
	case 'b':
		steve.PlayerX = 1 / 2 + 0.5;
		steve.PlayerY = (20);
		steve.PlayerZ = 1 / 2 + 0.5;
		steve.dy = 0;
		break;
	case 'f':
		IDblocks++;
		if (IDblocks > blocks) IDblocks = 0;
		break;

	case 32:
		steve.jump();
		break;

	case 27: {
		exit(0);
	}
	}

void processNormalKeysUP(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
	case 'W':
	case 's':
	case 'S':
		KeyFront = 0;
		break;
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		KeySide = 0;
		break;
}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -8.0);
	glRotatef(angle, 1.0, 1.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);

	//draw
	glBegin(GL_QUADS);
	//front
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	//back
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	//right
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	//left
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	//top
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	//bottom
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);

	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 2.0, 50.0);
	glMatrixMode(GL_MODELVIEW);

}
///////////////////
void timer(int)
{////////////
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	///I am so tired)))), but happy///
	angle += 0.8 * 4;
	if (angle > 360.0)
		angle = angle - 360.0;
}