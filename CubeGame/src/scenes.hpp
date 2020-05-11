bool trees(int, int, int); // функция-затычка. обьявляем ее, чтобы в этом файле оня была видна
void game() {
    hotbar.update();
    aim.update();
    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,
        0.0f, 1.0f, 0.0f);
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
    Draw_cubes();
    steve.update(0);
}
void load_game() {
    sf::Image im; im.loadFromFile("textures/heightmap1.jpg");

    for (int x = 0; x < quantity_cubes_x; x++)
        for (int z = 0; z < quantity_cubes_z; z++) {
            int c = im.getPixel(x, z).r / 10 + 10;
            for (int y = 0; y <= c; y++) {

                if (y == c) mass[x][y][z] = SUPER_GRASS;
                else if (y >= c - 4) mass[x][y][z] = DIRT;
                else mass[x][y][z] = STONE;

            }
        }
    for (int x = 0; x < quantity_cubes_x; x++)
        for (int z = 0; z < quantity_cubes_z; z++) {
            int c = im.getPixel(x, z).r / 10 + 10;
            for (int y = 4; y <= c; y++)
                if (x > 5 && x < quantity_cubes_x - 5 && z > 5 && x < quantity_cubes_z - 5)
                    if ((rand()) % 500 == 1)   trees(x, c, z);
        }
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