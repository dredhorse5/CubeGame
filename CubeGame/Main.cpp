﻿#include <Math.h>
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
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	//=======================================DRAW================================================
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(angle, 1.0, 2.0, 0.5);


	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++)
		{
			glTranslatef(x*size*2, y*size*2, z*size*2);
			Draw_cubes();
			glTranslatef(-x*size*2, -y*size*2, -z*size*2);
		}
	
	
	angle += 0.8 * 4;
	if (angle > 360.0)
		angle = angle - 360.0;


	//=======================================DRAW================================================
	glPopMatrix();
	glutSwapBuffers();
}
int main(int argc, char* argv[]) {
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


	glutMainLoop();
	return 0;
}


