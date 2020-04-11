#include <Math.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <SOIL.h>
#pragma comment(lib, "SOIL.lib")

GLuint dirt[1];
int View = 90; // angle of view
int FPS = 60; // 60
const int width = 1280, height = 720; // размер окна
float lx = 1.0f, lz = 0.0f, ly = 0.0f; // единичные вектора камеры
float angleX = 0.0f, angleY = 5.0f; // угол наклона камеры
int mouseXOld = 1, mouseYOld = 1; // старые коориднаты  мышки
int size = 1; // размер куба

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


void processNormalKeys(unsigned char key, int x, int y) {
    switch(key) {
    case 27:
        exit(0);
    }
}

void mouseMove(int x, int y) {
    if (mouseXOld != 0 or mouseYOld != 0) {
        angleX -= mouseXOld * 0.001f;
        angleY -= mouseYOld * 0.001f;

        if (angleY > 3.14 / 2) angleY = 3.14 / 2;
        if (angleY < -3.14 / 2) angleY = -3.14 / 2;

        mouseXOld = 0; mouseYOld = 0;

        // update camera's direction
        lx = float(sin(angleX));
        lz = float(-cos(angleX));
        ly = float(-tan(angleY));

    }
    else {

        mouseXOld = (width / 2) - x;
        mouseYOld = (height / 2) - y;
        glutWarpPointer((width / 2), (height / 2));
    }


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
    gluLookAt(0,         5,      0,       // координаты игрока
              0 + lx,    5+ly,   0 + lz,  // координаты единичного вектора камеры
              0.0f,      1.0f,   0.0f   );// координаты нормального вектора камеры. не трогаем. 

	glClearColor(0.5, 0.5, 0.5, 1.0); // задаем цвет фона R, G, B, а так же альфа компонента(A), которая задает непрозрачность
	//=======================================DRAW================================================



	for (int x = -10; x < 10; x++)
		for (int y = 0; y < 1; y++)
			for (int z = -10; z < 10; z++){
			    glTranslatef(x*size*2, y*size*2, z*size*2);
			    Draw_cubes();
			    glTranslatef(-x*size*2, -y*size*2, -z*size*2);
            }
	
	
	



	//=======================================DRAW================================================
	glPopMatrix();
	glutSwapBuffers();
}



int main() {
	
	glutInitWindowSize(width, height); // задает размеры окна
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // включаем цвет RGBA и двойную буферизацию
	glutCreateWindow("cubes"); // создаем окно
	glEnable(GL_DEPTH_TEST); // включаем тест глубины 
	glutTimerFunc(1000 / FPS, timer, 0); // ограничение FPS
	glEnable(GL_TEXTURE_2D); // включаем 2D текстуры
	
    glEnable(GL_CULL_FACE); // включаем режим, в котором мы рисуем стороны куба либо по часовой, либо против часовой стрелки
    glFrontFace(GL_CCW);  // говорим, что идем против часовой стрелки.
	glCullFace(GL_FRONT); // не рисуем переднюю часть. будет видна только задняя. почему отсекаем передню, а не заднюю? легче было так сделать)
	
    glutDisplayFunc(display); // основная функция рисования
	glutReshapeFunc(reshape); // функция, вызываеая при обновлении окна. нужна для правильного показа окна
	glutPassiveMotionFunc(mouseMove); //функция, которая отслеживает мышку в НЕ нажатом состоянии
	glutMotionFunc(mouseMove); // функция, которая отслеживает мышку в нажатом состоянии

	dirtTextures(width, height); // загружаем текстуру
	
    glutKeyboardFunc(processNormalKeys);
	

	glutMainLoop();
	return 0;
}
