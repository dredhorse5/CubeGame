
/**
    \brief функци€ дл€ подсвечивани€ кубов

    Ёта функци€ подсвечивает кубы, получа€ дл€ этого координаты, блока, на который смотрит игрок
    ћы увеличиваем немного размер куба локально дл€ этой функции, чтобы линии строились немного поверх куба, в не в нем.
    ѕотом с помощью   glTranslatef() мы подгон€ем , где будут рисоватьс€ лини.

    \param[in] cube_size передаем размер куба, чтобы локально его увеличить
    \param[in] X координата X, куда смотрит игрок
    \param[in] Y координата Y, куда смотрит игрок
    \param[in] Z координата Z, куда смотрит игрок
*/
void draw_lines_cubes(float cube_size, int X, int Y, int Z) {
    glLineWidth(2);
    glTranslatef(X * cube_size + cube_size / 2, Y * cube_size + cube_size / 2, Z * cube_size + cube_size / 2);
    cube_size = cube_size / 2 + 0.004;
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
    glTranslatef(-X * cube_size - cube_size / 2, -Y * cube_size - cube_size / 2, -Z * cube_size - cube_size / 2);
    glColor3d(1, 1, 1);

}

void Draw_one_tex_blocks(GLuint* tex, int X, int Y, int Z) {
	glBindTexture(GL_TEXTURE_2D, *tex);
	glBegin(GL_QUADS);
	///задн€€
	glColor3f(0.8, 0.8, 0.8);
	if ((steve.PlayerZ/2   > Z) && !mass[X][Y][Z + 1]) {
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
    }
    //передн€€
    if (steve.PlayerZ/2 < Z && !mass[X][Y][Z - 1]) {
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    //ѕ–ј¬јя
    glColor3f(0.7, 0.7, 0.7);
    if (steve.PlayerX/2 > X && !mass[X + 1][Y][Z]) {
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    //Ћ≈¬јя
    if (steve.PlayerX/2 < X && !mass[X - 1][Y][Z]) {
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glColor3f(0.5, 0.5, 0.5);
    //Ќ»∆Ќяя
    if (steve.PlayerY/2 < Y && !mass[X][Y - 1][Z]) {
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
    }
    glColor3f(1, 1, 1);
    //¬≈–’Ќяя
    if (steve.PlayerY/2 > Y && !mass[X][Y + 1][Z]) { // Y == 0 or 
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glEnd();
}

/**
	/brief рисование блоков с травой 


*/
void Draw_super_grass(int X, int Y, int Z)
{

    glBindTexture(GL_TEXTURE_2D, super_grass);
    glBegin(GL_QUADS);
    ///задн€€ 
    glColor3f(0.8, 0.8, 0.8); // cool glColor3f(1.8, 0.8, 0.8);
    if ((steve.PlayerZ / 2  > Z) && !mass[X][Y][Z + 1]) {
        glTexCoord2d(1, 0.5); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
    }
    //передн€€
    if ((steve.PlayerZ / 2 < Z) && !mass[X][Y][Z - 1]) { // Z == 0 or 
        glTexCoord2d(1, 0.5); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    glColor3f(0.7, 0.7, 0.7);
    //ѕ–ј¬јя
    if (steve.PlayerX / 2 > X && !mass[X + 1][Y][Z]) {
        glTexCoord2d(1, 0.5); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    //Ћ≈¬јя
    if (steve.PlayerX / 2 < X && !mass[X - 1][Y][Z]) { // X == 0 or 
        glTexCoord2d(1, 0.5); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glColor3f(0.5, 0.5, 0.5);
    //Ќ»∆Ќяя
    if (steve.PlayerY / 2 < Y && !mass[X][Y - 1][Z]) {
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 0.5); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
    }
    //¬≈–’Ќяя
    glColor3f(1, 1, 1);
    if (steve.PlayerY / 2 > Y && !mass[X][Y + 1][Z]) { // Y == 0 or 
        glTexCoord2d(1, 0.5); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glEnd();
}

/**
	/brief функци€ рисующа€ деревь€ 


*/
void Draw_tree_oak(int X, int Y, int Z) {

    glBindTexture(GL_TEXTURE_2D, tree_oak);
    glBegin(GL_QUADS);
    ///задн€€ 
    glColor3f(0.8, 0.8, 0.8); // cool glColor3f(1.8, 0.8, 0.8);
    if ((steve.PlayerZ / 2  > Z) && !mass[X][Y][Z + 1]) {
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
    }
    //передн€€
    if ((steve.PlayerZ / 2  < Z) && !mass[X][Y][Z - 1]) { // Z == 0 or 
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    glColor3f(0.7, 0.7, 0.7);
    //ѕ–ј¬јя
    if (steve.PlayerX / 2 > X && !mass[X + 1][Y][Z]) {
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    //Ћ≈¬јя
    if (steve.PlayerX / 2 < X && !mass[X - 1][Y][Z]) { // X == 0 or 
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glColor3f(0.5, 0.5, 0.5);
    //Ќ»∆Ќяя
    if (steve.PlayerY / 2 < Y && !mass[X][Y - 1][Z]) {
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
    }
    //¬≈–’Ќяя
    glColor3f(1, 1, 1);
    if (steve.PlayerY / 2 > Y && !mass[X][Y + 1][Z]) { // Y == 0 or 
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glEnd();

}

/**
	/brief рисование skybox


*/
void drawSkybox()
{
	glTranslatef(steve.PlayerX, steve.PlayerY, steve.PlayerZ);
	//==================================================================
	glBindTexture(GL_TEXTURE_2D, skybox_tex);
	glBegin(GL_QUADS);
	//задн€€
	glTexCoord2d(0.001f, 0.665f); glVertex3f(-400, -400, 400);
	glTexCoord2d(0.25f, 0.665f); glVertex3f(400, -400, 400);
	glTexCoord2d(0.25f, 0.334f); glVertex3f(400, 400, 400);
	glTexCoord2d(0.001f, 0.334f); glVertex3f(-400, 400, 400);
	//==================================================================
	//права€
	glTexCoord2d(0.25f, 0.666666f); glVertex3f(400, -400, 400);
	glTexCoord2d(0.5f, 0.666666f); glVertex3f(400, -400, -400);
	glTexCoord2d(0.5f, 0.334f); glVertex3f(400, 400, -400);
	glTexCoord2d(0.25f, 0.334f); glVertex3f(400, 400, 400);

	//передн€€
	glTexCoord2d(0.5f, 0.334f); glVertex3f(400, 400, -400);
	glTexCoord2d(0.5f, 0.666666f); glVertex3f(400, -400, -400);
	glTexCoord2d(0.75f, 0.666666f); glVertex3f(-400, -400, -400);
	glTexCoord2d(0.75f, 0.334f); glVertex3f(-400, 400, -400);

	//лева€
	glTexCoord2d(0.75, 0.666666f); glVertex3f(-400, -400, -400);
	glTexCoord2d(0.9999f, 0.666666f); glVertex3f(-400, -400, 400);
	glTexCoord2d(0.9999f, 0.334f); glVertex3f(-400, 400, 400);
	glTexCoord2d(0.75f, 0.334f); glVertex3f(-400, 400, -400);

	//нижн€€
	glTexCoord2d(0.5f, 0.999f); glVertex3f(-400, -400, -400);
	glTexCoord2d(0.5f, 0.6666f);  glVertex3f(400, -400, -400);
	glTexCoord2d(0.25f, 0.6666f); glVertex3f(400, -400, 400);
	glTexCoord2d(0.25f, 0.999f);  glVertex3f(-400, -400, 400);
	//==================================================================

	//верхн€€
	glBegin(GL_POLYGON);
	glTexCoord2d(0.2501f, 0.001f); glVertex3f(-400, 400, 400);
	glTexCoord2d(0.2501f, 0.33333f); glVertex3f(400, 400, 400);
	glTexCoord2d(0.4999f, 0.33333f); glVertex3f(400, 400, -400);
	glTexCoord2d(0.4999f, 0.001f);  glVertex3f(-400, 400, -400);

	glEnd();
	glTranslatef(-steve.PlayerX, -steve.PlayerY, -steve.PlayerZ);
}
