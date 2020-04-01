#include <Math.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <SOIL.h>
//#include "load_texures.hpp"
#pragma comment(lib, "SOIL.lib")
//#define GL_CLAMP_TO_EDGE 0x812F

GLuint dirt[1];
int View = 90; // angle of view
int FPS = 60; // 60
float angle = 0.0f;
float angls = 0;
float angln = 0;
int size = 1;
void dirtTextures(int W, int H) {
	unsigned char* topу = SOIL_load_image("textures/dirt.png", &W, &H, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &dirt[0]);
	glBindTexture(GL_TEXTURE_2D, dirt[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, topу);
	SOIL_free_image_data(topу);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void reshape(int w, int h){
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(View, ratio, 0.1f, 360.0f);
	glMatrixMode(GL_MODELVIEW);

}
void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	///I am so tired)))), but happy///
}
void Draw_cubes() {
    glBindTexture(GL_TEXTURE_2D, dirt[0]);
	glColor3f(1.0, 1.0, 1.0);
    ///задняя
        glBegin(GL_POLYGON);
        glTexCoord2d(1, 1); glVertex3f(1, -1, 1);
        glTexCoord2d(0, 1); glVertex3f(-1, -1, 1);
        glTexCoord2d(0, 0); glVertex3f(-1, 1, 1);
        glTexCoord2d(1, 0); glVertex3f(1, 1, 1);
        glEnd();
    //передняя
        glBegin(GL_POLYGON);
        glTexCoord2d(1, 1); glVertex3f(-1, -1, -1);
        glTexCoord2d(0, 1); glVertex3f(1, -1, -1);
        glTexCoord2d(0, 0); glVertex3f(1, 1, -1);
        glTexCoord2d(1, 0); glVertex3f(-1, 1, -1);
        glEnd();
    
    //ПРАВАЯ
        glBegin(GL_POLYGON);
        glTexCoord2d(1, 1); glVertex3f(1, -1, -1);
        glTexCoord2d(0, 1); glVertex3f(1, -1, 1);
        glTexCoord2d(0, 0); glVertex3f(1, 1, 1);
        glTexCoord2d(1, 0); glVertex3f(1, 1, -1);
        glEnd();
    
    //ЛЕВАЯ
        glBegin(GL_POLYGON);
        glTexCoord2d(1, 1); glVertex3f(-1, -1, 1);
        glTexCoord2d(0, 1); glVertex3f(-1, -1, -1);
        glTexCoord2d(0, 0); glVertex3f(-1, 1, -1);
        glTexCoord2d(1, 0); glVertex3f(-1, 1, 1);
        glEnd();
    //НИЖНЯЯ
        glBegin(GL_POLYGON);
        glTexCoord2d(1, 1); glVertex3f(-1, -1, 1);
        glTexCoord2d(0, 1); glVertex3f(1, -1, 1);
        glTexCoord2d(0, 0); glVertex3f(1, -1, -1);
        glTexCoord2d(1, 0); glVertex3f(-1, -1, -1);
        glEnd();
    
    //ВЕРХНЯЯ
        glBegin(GL_POLYGON);
        glTexCoord2d(1, 1); glVertex3f(-1, 1, -1);
        glTexCoord2d(0, 1); glVertex3f(1, 1, -1);
        glTexCoord2d(0, 0); glVertex3f(1, 1, 1);
        glTexCoord2d(1, 0); glVertex3f(-1, 1, 1);
        glEnd();
    
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//=======================================DRAW================================================
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(1*angle, 1*angls, 1*angln, 0.5);


	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++)
		{
			glTranslatef(x*size*2, y*size*2, z*size*2);
			Draw_cubes();
			glTranslatef(-x*size*2, -y*size*2, -z*size*2);
		}
	
	
	
	//angle += 0.8 * 4;
	//if (angle > 360.0)
		//angle = angle - 360.0;


	//=======================================DRAW================================================
	glPopMatrix();
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key = GLUT_KEY_LEFT) {
		angle = 20.2;
	}
	else {
		angle = 0;
	}
	

	if (key = GLUT_KEY_RIGHT) {
		angls = 20.2;
	}
	else {
		angls = 0;
	}
		

	if (key = GLUT_KEY_UP) {
		angln = 20.2;
	}
	else {
		angln = 0;
	}		
		
}

int main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("cubes");
	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(1000 / FPS, timer, 0); // limit fps
	glEnable(GL_TEXTURE_2D);
	
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);

	dirtTextures(500, 500);
	glutKeyboardFunc(processNormalKeys);

	glutMainLoop();
	return 0;
}
