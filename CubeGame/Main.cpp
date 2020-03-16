//#include <SOIL.h>
#include <glut.h>
#include <iostream>

float angle = 0.0f;

void changeSize(int w, int h) {
	// ïðåäîòâðàùåíèå äåëåíèÿ íà íîëü
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// èñïîëüçóåì ìàòðèöó ïðîåêöèè
	glMatrixMode(GL_PROJECTION);
	// îáíóëÿåì ìàòðèöó
	glLoadIdentity();
	// óñòàíîâèòü ïàðàìåòðû âüþïîðòà
	glViewport(0, 0, w, h);
	// óñòàíîâèòü êîððåêòíóþ ïåðñïåêòèâó
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// âåðíóòüñÿ ê ìàòðèöå ïðîåêöèè
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	///////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(0.5, -0.9, 0.0);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char* argv[]) {

	// èíèöèàëèçàöèÿ
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Óðîê 1");

	// ðåãèñòðàöèÿ îáðàòíûõ âûçîâîâ
	glutDisplayFunc(renderScene);

	// Îñíîâíîé öèêë GLUT
	glutMainLoop();

	return 1;
}