void Draw_one_tex_blocks(GLuint *tex, int X, int Y, int Z) {
    glBindTexture(GL_TEXTURE_2D, *tex);
    glBegin(GL_QUADS);
    ///çàäíÿÿ
    glColor3f(0.8, 0.8, 0.8);
    if (!mass[X][Y][Z + 1]) {
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
    }
    //ïåðåäíÿÿ
    if (!mass[X][Y][Z - 1]) {
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    //ÏÐÀÂÀß
    glColor3f(0.7, 0.7, 0.7);
    if (!mass[X + 1][Y][Z]) {
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    //ËÅÂÀß
    if (!mass[X - 1][Y][Z]) {
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glColor3f(0.5, 0.5, 0.5);
    //ÍÈÆÍßß
    if (!mass[X][Y - 1][Z]) {
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
    }
    glColor3f(1, 1, 1);
    //ÂÅÐÕÍßß
    if (!mass[X][Y + 1][Z]) { // Y == 0 or 
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glEnd();
}
void Draw_super_grass(int X, int Y, int Z)
{

    glBindTexture(GL_TEXTURE_2D, super_grass);
    glBegin(GL_QUADS);
    ///çàäíÿÿ 
    glColor3f(0.8, 0.8, 0.8); // cool glColor3f(1.8, 0.8, 0.8);
    if (!mass[X][Y][Z + 1]) {
        glTexCoord2d(1, 0.5); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
    }
    //ïåðåäíÿÿ
    if (!mass[X][Y][Z - 1]) { // Z == 0 or 
        glTexCoord2d(1, 0.5); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    glColor3f(0.7, 0.7, 0.7);
    //ÏÐÀÂÀß
    if (!mass[X + 1][Y][Z]) {
        glTexCoord2d(1, 0.5); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    //ËÅÂÀß
    if (!mass[X - 1][Y][Z]) { // X == 0 or 
        glTexCoord2d(1, 0.5); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glColor3f(0.5, 0.5, 0.5);
    //ÍÈÆÍßß
    if (!mass[X][Y - 1][Z]) {
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 0.5); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
    }
    //ÂÅÐÕÍßß
    glColor3f(1, 1, 1);
    if (!mass[X][Y + 1][Z]) { // Y == 0 or 
        glTexCoord2d(1, 0.5); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0.5); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glEnd();
}
void Draw_tree_oak(int X, int Y, int Z) {

    glBindTexture(GL_TEXTURE_2D, tree_oak);
    glBegin(GL_QUADS);
    ///çàäíÿÿ 
    glColor3f(0.8, 0.8, 0.8); // cool glColor3f(1.8, 0.8, 0.8);
    if (!mass[X][Y][Z + 1]) {
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
    }
    //ïåðåäíÿÿ
    if (!mass[X][Y][Z - 1]) { // Z == 0 or 
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    glColor3f(0.7, 0.7, 0.7);
    //ÏÐÀÂÀß
    if (!mass[X + 1][Y][Z]) {
        glTexCoord2d(1, 1); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
    }
    //ËÅÂÀß
    if (!mass[X - 1][Y][Z]) { // X == 0 or 
        glTexCoord2d(1, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(1, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glColor3f(0.5, 0.5, 0.5);
    //ÍÈÆÍßß
    if (!mass[X][Y - 1][Z]) {
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
    }
    //ÂÅÐÕÍßß
    glColor3f(1, 1, 1);
    if (!mass[X][Y + 1][Z]) { // Y == 0 or 
        glTexCoord2d(0.5, 1); glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 1); glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glTexCoord2d(0, 0); glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glTexCoord2d(0.5, 0); glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
    }
    glEnd();

}