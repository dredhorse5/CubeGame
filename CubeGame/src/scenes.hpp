void hotbar_func() {
    glPushMatrix();
    for (int i = 0; i <= blocks; i++) {
        glTranslatef(-0.177 + i * 0.04411, -0.1759, 0);
        if(i == IDblocks)
            icon_selecter.update();

        switch (i) {
        case STONE:
            stone_icon.update();
            break;
        case SUPER_GRASS:
            super_grass_icon.update();
            break;
        case DIRT:
            dirt_icon.update();
            break;
        case COBBLESTONE:
            cobblestone_icon.update();
            break;
        case PLANKS:
            planks_icon.update();
            break;
        case TREE_OAK:
            tree_oak_icon.update();
            break;
        case LEAVES:
            leaves_icon.update();
            break;
        case BRICKS:
            bricks_icon.update();
            break;
        }
        glTranslatef(0.177 - i * 0.04411, 0.1759, 0);
    }
    glPopMatrix();
    hotbar.update();
}
/**
    /brief ������� ��� ����

    ��� ������������ ��� �������� ����
*/
void game() {
    hotbar_func();
    aim.update();

    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,
        0.0f, 1.0f, 0.0f);
	drawSkybox();
    // start ��� ����� ���� ��������� ����� ����� �������, ����� ����� �������� ������ �������
    newtime = clock();
    double times = newtime - oldtime;
    oldtime = clock();
    // end ��� ����� ���� ��������� ����� ����� �������, ����� ����� �������� ������ �������
    Draw_cubes();
    pig.update(times, steve.PlayerX, steve.PlayerZ);
    steve.update(times);

}
/**
	/brief ������� ����


*/
void game_menu() {
    slider.update();
    exit_touch.update();
    exit_and_save.update();
    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,
        0.0f, 1.0f, 0.0f);
	drawSkybox();
    Draw_cubes();
    steve.update(0);
    pig.update(0, steve.PlayerX, steve.PlayerZ);
    glColor3f(1, 1, 1);
}
/**
	/brief ���� �������� ����

	������� ��� �������� ���� 

*/
void load_menu() {

    static float angle = 0.0f;
    glPushMatrix();
    glRotatef(angle, 0, 0, 1);
    save_icon.update();
    glPopMatrix();

    background_main_menu.update();
    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,
        0.0f, 1.0f, 0.0f);
    angle += 0.1;
}
/**
	/brief ������� ����

	���� � ������� �����(����)


*/
void main_menu() {
    world1.update();
    world2.update();
    world3.update();
    world4.update();
    exit_touch.update();
    background_main_menu.update();

    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,
        0.0f, 1.0f, 0.0f);
    steve.update(0);
    glColor3f(1, 1, 1);
}