﻿#include <cmath>
#include <stdio.h>
#include <iostream>
#include "glut.h" 
#include "SOIL.h"
#include <ctime>
#include <SFML/Graphics.hpp>
//#include <SFML/OpenGL.hpp>
#pragma comment(lib, "SOIL.lib")
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
GLuint GUI_tex;
GLuint dirt, dirt_icon_tex;
GLuint stone, stone_icon_tex;
GLuint super_grass, super_grass_icon_tex;
GLuint leaves, leaves_icon_tex;
GLuint tree_oak, tree_oak_icon_tex;
GLuint skybox_tex;

int FPS = 60; ///< ограничение по FPS
const int quantity_cubes_x = 250; ///< колличество блоков по оси x
const int quantity_cubes_y = 50;  ///< колличество блоков по оси y
const int quantity_cubes_z = 250; ///< колличество блоков по оси z
const int width = 1280; ///< ширина окна
const int height = 720; ///< высота окна
int W = width;
int H = height;
float lx = 1.0f; ///< x координата единичного вектора направления камеры
float lz = 0.0f; ///< z координата единичного вектора направления камеры
float ly = 0.0f; ///< y координата единичного вектора направления камеры
float angleX = 0.0f; ///< угол поворота камеры в плоскости XZ
float angleY = 5.0f; ///< угол поворота камеры по оси Y
int mouseXOld = 1; ///< старая х координата мыши
int mouseYOld = 1; ///< старая y координата мыши
float KeyFront = 0; ///< ключ к изменению скорости вперед/назад
float KeySide = 0; ///< ключ к изменению скорости вбок
int cube_size = 2; ///< размер куба
int mass[quantity_cubes_x][quantity_cubes_y][quantity_cubes_z]; ///< массив мира, по которому строится сам мир
bool mLeft = 0; ///< состояние левой кнопки мыши
bool mRight = 0; ///< состояние правой кнопки мыши
time_t oldtime = 1;
time_t newtime = 1;
char game_now = 2; // состояние игры в данный момент
char world_now = 0; // определят, в каком мире мы играем. в игре 4 мира
short int IDblocks = 1;
short int blocks = 8;
int visible_range = 40;


char tree_mass[7][5][5] = { {
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 6, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0} },
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 6, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0} },
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 6, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0} },
{
{7, 7, 7, 7, 7},
{7, 7, 7, 7, 7},
{7, 7, 6, 7, 7},
{7, 7, 7, 7, 7},
{7, 7, 7, 7, 7} },
{
{7, 7, 7, 7, 7},
{7, 7, 7, 7, 7},
{7, 7, 6, 7, 7},
{7, 7, 7, 7, 7},
{7, 7, 7, 7, 7} },
{
{0, 0, 0, 0, 0},
{0, 7, 7, 7, 0},
{0, 7, 6, 7, 0},
{0, 7, 7, 7, 0},
{0, 0, 0, 0, 0} },
{
{0, 0, 0, 0, 0},
{0, 0, 7, 0, 0},
{0, 7, 7, 7, 0},
{0, 0, 7, 0, 0},
{0, 0, 0, 0, 0} }, };
void draw_lines_cubes(float , int , int , int );
#include "GUI.hpp"


enum Blocks {
    AIR,
    STONE,
    SUPER_GRASS,
    DIRT,
    COBBLESTONE,
    PLANKS,
    TREE_OAK,
    LEAVES,
    BRICKS
};
enum game_types {
    GAME,
    GAME_MENU,
    MAIN_MENU,
    LOAD_MENU
};
class Player {
public:
    float PlayerX; ///< Координата игрока по оси X
    float PlayerY; ///< Координата игрока по оси Y
    float PlayerZ; ///< Координата игрока по оси Z
    float dx;      ///< Общая скорость игрока по оси x
    float dy;      ///< Общая скорость игрока по оси y
    float dz;      ///< Общая скорость игрока по оси z
    float dSideX;  ///< поперечная скорость по оси x
    float dSideZ;  ///< поперечная скорость по оси z
    float dFrontX; ///< продольная скорость по оси x
    float dFrontZ; ///< продольная скорость по оси z
    float w;       ///< ширина игрока
    float h;       ///< высота игрока
    float d;       ///< Глубина игрока
    bool onGround; ///< определяет, косаетесь ли вы пола
    float speed;   ///< скорость игрока
    float View;    ///< угол обзора
    /**
        \brief Конструктор класса

        \param[in] x0 координата спавна игрока по оси x
        \param[in] y0 координата спавна игрока по оси y
        \param[in] z0 координата спавна игрока по оси z
    */
    Player(float x0, float y0, float z0) {
        PlayerX = x0; PlayerY = y0; PlayerZ = z0;
        dx = 0; dy = 0; dz = 0;
        dSideX = 0; dSideZ = 0;
        dFrontX = 0; dFrontZ = 0;
        w = 0.5f; h = 1.9f; d = 0.5f; speed = 0.5;
        onGround = false;
        View = 90; // угол обзора
    }
    /**
        \brief проверяет на столкновение
    */
    bool check(int x, int y, int z) {
        if ((x < 0) || (x > quantity_cubes_x) ||
            (y < 0) || (y > quantity_cubes_y) ||
            (z < 0) || (z > quantity_cubes_z)) return false;
        return mass[x][y][z];


    }
    /**
        \brief основаня функцию обновления игрока

        \param[in] time время 1 кадра
    */
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
            dSideZ = lx * speed * KeySide * time / 50;
        }
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
    /////
    /**
        \brief обрабатывает нажатие мыши

        эта функция понимает, какая кнопка мыши нажата и за счет этого либо ставит, либо разрушает блоки

    */
    void mousePressed() {
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
                    mass[oldX][oldY][oldZ] = IDblocks; // IDblocks // перед столкновением записывали сторые координаты луча.
                    //если столкнулись с блоком- ставим блок на предыдущих координатах, где луч еще "шел"
                    //mass[int(PlayerX / 2)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2)] = 0;
                    //mass[int(PlayerX / 2)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    //mass[int(PlayerX / 2)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    //mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2)] = 0;
                    //mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 + h / 2 - 0.05)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;

                    //mass[int(PlayerX / 2)][int(PlayerY / 2)][int(PlayerZ / 2)] = 0;
                    //mass[int(PlayerX / 2)][int(PlayerY / 2)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    //mass[int(PlayerX / 2)][int(PlayerY / 2)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    //mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2)][int(PlayerZ / 2)] = 0;
                    //mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2)][int(PlayerZ / 2)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;

                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    //mass[int(PlayerX / 2)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2)] = 0;
                    //mass[int(PlayerX / 2)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 + d / 2 - 0.01)] = 0;
                    //mass[int(PlayerX / 2)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2 - d / 2 + 0.01)] = 0;
                    //mass[int(PlayerX / 2 + w / 2 - 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2)] = 0;
                    //mass[int(PlayerX / 2 - w / 2 + 0.01)][int(PlayerY / 2 - h / 2 + 0.01)][int(PlayerZ / 2)] = 0;

                    break;
                }
                break;

            }

            oldX = X; oldY = Y; oldZ = Z; // записываем старые координаты луча

            
        }
        //}
        mLeft = mRight = false;
    }
  
    /**
        \brief определяет поведение при столкновении с колизией 

        эта функция принимает на вход скорости по осям игрока, и при столкновении с клизией определяет, как должен вести себя игрок
    */
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
    
    /// прыжок игрока
    void jump() {
        if (onGround) {
            onGround = false;
            dy = 0.8;
        }
    }
};
Player steve(quantity_cubes_x/ 2 + 2, 60, quantity_cubes_z / 2); // создаем обьект
#include "draw.hpp"
void Draw_cubes() {
    // цикл для рисования блоков
    for (int x = steve.PlayerX / 2 - visible_range; x < steve.PlayerX / 2 + visible_range; x++) // строим блоки  на расстоянии 10 блоков в обе стороны от координаты X игрока
        for (int y = 4; y < quantity_cubes_y; y++)
            for (int z = steve.PlayerZ / 2 - visible_range; z < steve.PlayerZ / 2 + visible_range; z++) {// строим блоки  на расстоянии 10 блоков в обе стороны от координаты Z игрока


                if (x < 0 || x > quantity_cubes_x) continue;
                if (z < 0 || z > quantity_cubes_z) continue;
                int type = mass[x][y][z];
                if (!type || ((mass[x + 1][y][z] && mass[x - 1][y][z]
                            && mass[x][y + 1][z] && mass[x][y - 1][z])
                            && mass[x][y][z + 1] && mass[x][y][z - 1]))continue;



                glPushMatrix();

                glTranslatef(x * cube_size + cube_size / 2, y * cube_size + cube_size / 2, z * cube_size + cube_size / 2);
                switch (type){
                    case STONE:         Draw_one_tex_blocks(&stone,     x, y, z);
                    case DIRT:          Draw_one_tex_blocks(&dirt,      x, y, z);
                    case SUPER_GRASS:   Draw_super_grass(               x, y, z);
                    case TREE_OAK:      Draw_tree_oak(                  x, y, z);
                    case LEAVES:        Draw_one_tex_blocks(&leaves,    x, y, z);
                   
                }

             
                 glPopMatrix();

            }
}
#include "scenes.hpp"
/**
    \brief главная функция программы

    циклично вызывается. 1 вызов- 1 кадр. обновляет все, что находится в мире- положение игрока, его угол поворота. так же
    обновляет каждым разом мир - рисует его

*/
void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфера цвета и глубины
	glPushMatrix();

    switch (game_now) {
    case GAME:
        game();
        break;
    case GAME_MENU:
        game_menu();
        break;
    case MAIN_MENU:
        main_menu();
        break;
    }
	glPopMatrix();
	glutPostRedisplay();
	glFinish();
}
void reshape(int w, int h) {
    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(steve.View, ratio, 0.1f, 693.0f);
    glMatrixMode(GL_MODELVIEW);
}
#include "builders.hpp"
#include "load_textures.hpp"
#include "mouse_and_keyboard.hpp"
/**
    \brief точка входа в программу

    устанавливает все настройки библиотеки GLUT, а так же заполняет массив , по которому будет в дальнейшем строиться мир

*/








int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitWindowSize(width, height); // задает размеры окна
	glutInitDisplayMode(GLUT_RGBA /*| GLUT_DOUBLE*/); // включаем цвет RGBA и двойную буферизацию
	glutCreateWindow("mass"); // создаем окно
	glEnable(GL_DEPTH_TEST); // включаем тест глубины 
	glEnable(GL_TEXTURE_2D); // включаем 2D текстуры
	
    glEnable(GL_CULL_FACE); // включаем режим, в котором мы рисуем стороны куба либо по часовой, либо против часовой стрелки
    glFrontFace(GL_CCW);  // говорим, что идем против часовой стрелки.
	glCullFace(GL_FRONT); // не рисуем переднюю часть. будет видна только задняя. почему отсекаем передню, а не заднюю? легче было так сделать)
	
    glutDisplayFunc(display); // основная функция рисования
	glutReshapeFunc(reshape); // функция, вызываеая при обновлении окна. нужна для правильного показа окна
	
    glutPassiveMotionFunc(mouseMove); //функция, которая отслеживает мышку в НЕ нажатом состоянии
	glutMotionFunc(mouseMove); // функция, которая отслеживает мышку в нажатом состоянии
    
    glutMouseFunc(mouseButton); // Обрабатываем нажатие мыши

    if(game_now == GAME) glutSetCursor(GLUT_CURSOR_NONE);
    else glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    textures();
	

    glutKeyboardFunc(processNormalKeys);// функция отработки нажатия(без отжатия) клавиш
	glutKeyboardUpFunc(processNormalKeysUP); // функция отжатия клавишь

	glutMainLoop(); // говорим, что функция display играется циклично
	return 0; 
}