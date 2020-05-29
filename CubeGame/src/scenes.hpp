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
    /brief функци€ дл€ игры

    она обрабатывает все механики игры
*/
void game() {
    hotbar_func(); // рисуем хотбар
    aim.update(); // рисуем крестик на экране(прицел)

    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,
        0.0f, 1.0f, 0.0f); //функци€ дл€ обновлени€ камеры
	drawSkybox(); // рисуем небо
    // start эта часть кода вычисл€ет врем€ между кадрами, чтобы игрок двигалс€ засчет времени
    newtime = clock();
    double times = newtime - oldtime; //узнаем врем€ между кадрами
    oldtime = clock();
    // end эта часть кода вычисл€ет врем€ между кадрами, чтобы игрок двигалс€ засчет времени
    Draw_cubes(); // функци€, котора€ рисует сам мир
    pig.update(times, steve.PlayerX, steve.PlayerZ); // ќбвновл€ем свинку
    steve.update(times); // обвновл€ем все, что св€звно с игроком

}
/**
	/brief игровое меню


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
    glColor3f(1, 1, 1); // костыль
}
/**
	/brief меню загрузки мира

	активно при загрузки мира 

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
	/brief главное меню

	меню с выбором миров(карт)


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
    glColor3f(1, 1, 1); // костыль
}