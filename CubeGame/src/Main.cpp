#include <Math.h>
#include <stdio.h>
#include <iostream>
#include <glut.h> 
#include <SOIL.h>
#include <ctime>
#include <SFML/Graphics.hpp>
#pragma comment(lib, "SOIL.lib")

GLuint dirt[1];
int View = 90; // angle of view
int FPS = 60; // 60
const int quantity_cubes_x = 200;
const int quantity_cubes_y = 50;
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
bool mLeft = 0, mRight = 0; // mouse bottons
float angle;
void draw_lines_cubes(float cube_size, int X, int Y, int Z) {
    glLineWidth(2);
    cube_size = cube_size / 2 + 0.004;
    glTranslatef(X * 2 + 1, Y * 2 + 1, Z * 2 + 1);
    glBegin(GL_LINES);
    glColor3d(0, 0, 0);

    glVertex3f(-cube_size, -cube_size, -cube_size);
    glVertex3f(-cube_size, cube_size, -cube_size);

    glVertex3f(cube_size, -cube_size, -cube_size);
    glVertex3f(cube_size, cube_size, -cube_size);

    glVertex3f(cube_size, -cube_size, cube_size);
    glVertex3f(cube_size, cube_size, cube_size);

    glVertex3f(-cube_size, -cube_size, cube_size);
    glVertex3f(-cube_size, cube_size, cube_size);

    glVertex3f(-cube_size, -cube_size, -cube_size);
    glVertex3f(cube_size, -cube_size, -cube_size);

    glVertex3f(cube_size, -cube_size, -cube_size);
    glVertex3f(cube_size, -cube_size, cube_size);

    glVertex3f(cube_size, -cube_size, cube_size);
    glVertex3f(-cube_size, -cube_size, cube_size);

    glVertex3f(-cube_size, -cube_size, cube_size);
    glVertex3f(-cube_size, -cube_size, -cube_size);

    glVertex3f(-cube_size, cube_size, -cube_size);
    glVertex3f(cube_size, cube_size, -cube_size);

    glVertex3f(cube_size, cube_size, -cube_size);
    glVertex3f(cube_size, cube_size, cube_size);

    glVertex3f(cube_size, cube_size, cube_size);
    glVertex3f(-cube_size, cube_size, cube_size);

    glVertex3f(-cube_size, cube_size, cube_size);
    glVertex3f(-cube_size, cube_size, -cube_size);

    glEnd();
    glTranslatef(-(X * 2) - 1, -Y * 2 - 1, -Z * 2 - 1);
    glColor3d(1, 1, 1);

}

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
    bool check(int x, int y, int z) {
        if ((x < 0) or (x > quantity_cubes_x) or
            (y < 0) or (y > quantity_cubes_y) or
            (z < 0) or (z > quantity_cubes_z)) return false;
        return mass[x][y][z];


    }
    void update(float time) {

        if (PlayerY < 0) {
            PlayerY = 20 * cube_size;
            dy = 0;
        }

        mousePressed();

        if (KeyFront) {
            dFrontX = lx * speed * KeyFront * time / 50;
            dFrontZ = lz * speed * KeyFront * time / 50;
        }
        if (KeySide) {
            dSideX = -lz * speed * KeySide * time / 50;
        }
            dSideZ = lx * speed * KeySide * time / 50;

        dy -= 0.12 * (time / 50);
        onGround = 0;

        dx = dSideX + dFrontX;
        PlayerX += dx;
        collision(dx, 0, 0);
        PlayerY += dy * (time / 50);
        collision(0, dy, 0);
        dz = dSideZ + dFrontZ;
        PlayerZ += dz;
        collision(0, 0, dz);
        //one.join();


        dx = dz = dSideX = dSideZ = dFrontX = dFrontZ = 0;
    }
    void mousePressed() { // обрабатываем нажатие кнопки 
        //if (mRight or mLeft) {
        float mousex = PlayerX;
        float mousey = PlayerY + h / 2;
        float mousez = PlayerZ;
        int  X = 0, Y = 0, Z = 0;
        int oldX = 0, oldY = 0, oldZ = 0;
        float dist = 0.0f;

        while (dist < 80) {
            dist += 0.2; // пускаем луч из головы , пока он не коснется какого-нибудь блока
            mousex += lx / 50; X = mousex / cube_size;
            mousey += ly / 50; Y = mousey / cube_size;
            mousez += lz / 50; Z = mousez / cube_size;

            if (check(X, Y, Z)) {
				draw_lines_cubes(cube_size, X, Y, Z);
                if (mLeft) { mass[X][Y][Z] = 0; break; } // если нажата левая кнопка- уничтожаем блок
                if (mRight) { // если правая кнопка- ставим блок
                    // перед этим проверяем, чтобы блоки не поставились в "игроке"
                    mass[oldX][oldY][oldZ] = 1; // IDblocks // перед столкновением записывали сторые координаты луча.
                    //если столкнулись с блоком- ставим блок на предыдущих координатах, где луч еще "шел"
                    mass[int(PlayerX / 2)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2)] = 0;
                    mass[int(PlayerX / 2)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;

                    mass[int(PlayerX / 2)][int(PlayerY / 2)][int(PlayerZ / 2)] = 0;
                    mass[int(PlayerX / 2)][int(PlayerY / 2)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2)][int(PlayerY / 2)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2)][int(PlayerZ / 2)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2)][int(PlayerZ / 2)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;

                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    mass[int(PlayerX / 2)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2)] = 0;
                    mass[int(PlayerX / 2)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2)] = 0;

                    break;
                }
                break;
            }

            oldX = X; oldY = Y; oldZ = Z; // записываем старые координаты луча
        }
        //}
        mLeft = mRight = false;
    }
    void collision(float Dx, float Dy, float Dz) {
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
    void jump() {
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

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        switch (state) {
        case GLUT_DOWN:		//Если нажата
            mLeft = true;
            break;
        case GLUT_UP:      // если опущена
            mLeft = false;
            break;
        }
    }

    if (button == GLUT_RIGHT_BUTTON) {
        switch (state) {
        case GLUT_DOWN:		//Если нажата
            mRight = true;
            break;
        case GLUT_UP:      // если опущена
            mRight = false;
            break;
        }
    }
    //if (button == GLUT_WHEEL_DOWN)
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
    case 32:
        steve.jump();
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
    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,// координаты игрока
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,  // координаты единичного вектора камеры
              0.0f,                 1.0f,               0.0f               );// координаты нормального вектора камеры. не трогаем. 

	glClearColor(0.5, 0.5, 0.5, 1.0); // задаем цвет фона R, G, B, а так же альфа компонента(A), которая задает непрозрачность
	//=======================================DRAW================================================


    // цикл для рисования блоков
	for (int x = steve.PlayerX/2 - 10; x < steve.PlayerX/2 + 10; x++) // строим блоки  на расстоянии 10 блоков в обе стороны от координаты X игрока
		for (int y = 4; y < quantity_cubes_y; y++)
			for (int z = steve.PlayerZ/2 - 10; z < steve.PlayerZ/2 + 10; z++){// строим блоки  на расстоянии 10 блоков в обе стороны от координаты Z игрока


				if (mass[x][y][z] == 1){ // если в этом месте есть блок, то рисуем его
					glTranslatef(x * cube_size + cube_size/2  , y * cube_size + cube_size / 2, z * cube_size + cube_size / 2);
					Draw_cubes();
                    glTranslatef(-x * cube_size - cube_size / 2, -y * cube_size - cube_size / 2, -z * cube_size - cube_size / 2);
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
	glutCreateWindow("mass"); // создаем окно
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
    glutMouseFunc(mouseButton); // Обрабатываем нажатие мыши

	dirtTextures(width, height); // загружаем текстуру
	

    glutKeyboardFunc(processNormalKeys); // функция отработки нажатия(без отжатия) клавиш
	glutKeyboardUpFunc(processNormalKeysUP); // функция отжатия клавишь
    // цикл для заполнения массива 
    sf::Image im; im.loadFromFile("textures/heightmap1.jpg");
    for (int x = 0; x < quantity_cubes_x; x++)
        for (int z = 0; z < quantity_cubes_z; z++) {
            int c = im.getPixel(x, z).r / 10 + 10;
            for (int y = 4; y <= c; y++) {
                mass[x][y][z] = 1;
            }
        }

	glutMainLoop(); // говорим, что функция display играется циклично
	return 0; 
}
