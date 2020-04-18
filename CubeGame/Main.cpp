#include <Math.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <SOIL.h>
#include <ctime>
#pragma comment(lib, "SOIL.lib")

GLuint dirt[1];
int View = 90; // angle of view
int FPS = 60; // 60
const int quantity_cubes_x = 200;
const int quantity_cubes_y = 20;
const int quantity_cubes_z = 200;
const int width = 1280, height = 720; // размер окна
float lx = 1.0f, lz = 0.0f, ly = 0.0f; // единичные вектора камеры
float angleX = 0.0f, angleY = 5.0f; // угол наклона камеры
int mouseXOld = 1, mouseYOld = 1; // старые коориднаты  мышки
float KeyFront = 0, KeySide = 0; // ключ к изменению перемещения вперед/назад
int cube_size = 2; // размер куба
int mass[quantity_cubes_x][quantity_cubes_y][quantity_cubes_z];
float deltaAngle = 0.0f;
float deltaMove = 0;
float x;
float angle;
float z;

class Player {
public:
    float PlayerX, PlayerY, PlayerZ;
    float dx, dy, dz;
    float dSideX, dSideZ;
    float dFrontX, dFrontZ;
    float w, h, d;
    bool onGround;
    float speed;
    float View; // угол обзора

    Player(float x0, float y0, float z0) {
        PlayerX = x0; PlayerY = y0; PlayerZ = z0;
        dx = 0; dy = 0; dz = 0;
        dSideX = 0; dSideZ = 0;
        dFrontX = 0; dFrontZ = 0;
        w = 0.5f; h = 1.9f; d = 0.5f; speed = 0.5;
        onGround = false;
        View = 90; // угол обзора
    }
    bool check(int x, int y, int z) { // функция для проверки столкновения
        if ((x < 0) or (x > quantity_cubes_x) or
            (y < 0) or (y > quantity_cubes_y) or
            (z < 0) or (z > quantity_cubes_z)) return false;
        return mass[x][y][z];

    }







    void update(float time) {

        if (PlayerY < 0) { // если игрок провалился под землю, то телепортируем его наверх
            PlayerY = 20 * cube_size;
            dy = 0;
        }


        if (KeyFront) { // если активно движение вперед- идем
            dFrontX = lx * speed * KeyFront * time / 50;
            dFrontZ = lz * speed * KeyFront * time / 50;
        }
        if (KeySide) {// если активно движение вперед- идем
            dSideX = -lz * speed * KeySide * time / 50;
            dSideZ = lx * speed * KeySide * time / 50;
        }

        dy -= 0.12 * (time / 50); // падения, независимое от счетчика FPS
        onGround = 0;

        dx = dSideX + dFrontX; // получаем общую скорость 
        PlayerX += dx; // обновляем координаты игрока
        //std::thread one(Player::*collision, dx, 0, 0);
        collision(dx, 0, 0); // проверяем столкновение по скорости dx
        PlayerY += dy * (time / 50);// обновляем координаты игрока
        collision(0, dy, 0);// проверяем столкновение по скорости dy
        dz = dSideZ + dFrontZ;// получаем общую скорость 
        PlayerZ += dz;// обновляем координаты игрока
        collision(0, 0, dz);// проверяем столкновение по скорости dz


        dx = dz = dSideX = dSideZ = dFrontX = dFrontZ = 0; // Обнуляем скорости
    }
    
    void collision(float Dx, float Dy, float Dz) { // функция для взаимодействия игрока с коллизией
        for (int X = (PlayerX - w) / cube_size; X < (PlayerX + w) / cube_size; X++)
            for (int Y = (PlayerY - h) / cube_size; Y < (PlayerY + h) / cube_size; Y++)
                for (int Z = (PlayerZ - d) / cube_size; Z < (PlayerZ + d) / cube_size; Z++)
                    if (check(X, Y, Z))
                    {
                        if (Dx > 0) PlayerX = X * cube_size - w;
                        if (Dx < 0) PlayerX = X * cube_size + cube_size + w;

                        if (Dy > 0) { PlayerY = Y * cube_size - h; dy = 0; }
                        if (Dy < 0) { PlayerY = Y * cube_size + cube_size + h; onGround = true; dy = 0; }

                        if (Dz > 0) PlayerZ = Z * cube_size - d;
                        if (Dz < 0) PlayerZ = Z * cube_size + cube_size + d;

                    }
    }
    void jump() { // прыжок
        if (onGround) {
            onGround = false;
            dy = 0.8;
        }
    }
};
Player steve(quantity_cubes_x/ 2 + 2, 60, quantity_cubes_z / 2); // создаем обьект
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
    case 27: // если клавиша esc(27) нажата, то выходим из программы
        exit(0);
	case 'W':
	case 'w':
		KeyFront = 1;
		break;
	case 'S':
	case 's':
		KeyFront = -1;
		break;
	case 'D':
	case 'd':
		KeySide = 1;
		break;
	case 'A':
	case 'a':
		KeySide = -1;
		break;
	default:
		KeyFront = 0;
		KeySide = 0;
		break;
    }
}

void processNormalKeysUP(unsigned char key, int x, int y) {
	switch (key) {
	case 'W':
	case 'w':
		KeyFront = 0;
		break;
	case 'S':
	case 's':
		KeyFront = 0;
		break;
	case 'D':
	case 'd':
		KeySide = 0;
		break;
	case 'A':
	case 'a':
		KeySide = 0;
		break;
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
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфера цвета и глубины
	glPushMatrix(); // сохраняем систему координат
    gluLookAt(steve.PlayerX,        steve.PlayerY,      steve.PlayerZ,       // координаты игрока
              steve.PlayerX + lx,   steve.PlayerY +ly,  steve.PlayerZ + lz,  // координаты единичного вектора камеры
              0.0f,                 1.0f,               0.0f               );// координаты нормального вектора камеры. не трогаем. 

	glClearColor(0.5, 0.5, 0.5, 1.0); // задаем цвет фона R, G, B, а так же альфа компонента(A), которая задает непрозрачность
	//=======================================DRAW================================================


    // цикл для рисования блоков
	for (int x = steve.PlayerX/2 - 10; x < steve.PlayerX/2 + 10; x++) // строим блоки  на расстоянии 10 блоков в обе стороны от координаты X игрока
		for (int y = 0; y < 20; y++)
			for (int z = steve.PlayerZ/2 - 10; z < steve.PlayerX/2 + 10; z++){// строим блоки  на расстоянии 10 блоков в обе стороны от координаты Z игрока


				if (mass[x][y][z] == 1){ // если в этом месте есть блок, то рисуем его
					glTranslatef(x * cube_size  , y * cube_size , z * cube_size );
					Draw_cubes();
                    glTranslatef(-x * cube_size, -y * cube_size, -z * cube_size);
				}
					
            }
	
	
	


    steve.update(10); // функция обновления обьекта
	//=======================================DRAW================================================
	glPopMatrix(); // загружаем систему коориднат
	glutSwapBuffers(); // меняем буфера
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
	
    glutKeyboardFunc(processNormalKeys); // функция отработки нажатия(без отжатия) клавиш
	glutKeyboardUpFunc(processNormalKeysUP); // функция отжатия клавишь
    // цикл для заполнения массива 
	for(int x = 0; x < quantity_cubes_x; x++)
		for(int y = 0; y < quantity_cubes_y; y++)
			for (int z = 0; z < quantity_cubes_z; z++) {
				if( (y == 5) or (rand() % 10 == 1)) {
					mass[x][y][z] = 1;
				}
				else {
					mass[x][y][z] = 0;
				}
			}

	glutMainLoop(); // говорим, что функция display играется циклично
	return 0; 
}
