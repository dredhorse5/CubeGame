bool trees(int, int, int); // функция-затычка. обьявляем ее, чтобы в этом файле оня была видна
void game() {
    hotbar.update();
    aim.update();
    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,
        0.0f, 1.0f, 0.0f);
	drawSkybox();
    // start эта часть кода вычисляет время между кадрами, чтобы игрок двигался засчет времени
    newtime = clock();
    double times = newtime - oldtime;
    oldtime = clock();
    // end эта часть кода вычисляет время между кадрами, чтобы игрок двигался засчет времени
    Draw_cubes();
    steve.update(times);
}
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
}
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
void load_game() {
    std::ifstream fout("world" + std::to_string(world_now) + ".txt", std::ifstream::binary);
    char n;

    if (fout) {
        for (int x = 0; x < quantity_cubes_x; x++)
            for (int y = 4; y < quantity_cubes_y; y++)
                for (int z = 0; z < quantity_cubes_z; z++) {
                    fout.get(n);
                    mass[x][y][z] = int(n) - 48;
                }
    }
    else {
        time_t seed;
        seed = time(NULL);
        sf::Image im; im.loadFromFile("textures/heightmap1.jpg");
        for (int x = 0; x < quantity_cubes_x; x++)
            for (int z = 0; z < quantity_cubes_z; z++) {
                int c = im.getPixel(x, z).r / 10 + 10;
                for (int y = 0; y <= c; y++) {

                    if (y == c)         mass[x][y][z] = Blocks::SUPER_GRASS;
                    else if (y > c - 3) mass[x][y][z] = Blocks::DIRT;
                    else                mass[x][y][z] = Blocks::STONE;
                }
            }

        for (int x = 0; x < quantity_cubes_x; x++)
            for (int z = 0; z < quantity_cubes_z; z++) {
                int c = im.getPixel(x, z).r / 10 + 10;
                for (int y = 4; y <= c; y++)
                    if (x > 5 and x < quantity_cubes_x - 5 and z > 5 and x < quantity_cubes_z - 5)
                        if ((rand() + seed) % 500 == 1)   trees(x, c, z);


            }
    }
    fout.close();
}
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