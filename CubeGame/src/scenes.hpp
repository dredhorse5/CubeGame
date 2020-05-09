void game() {
    double times;
    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,
        0.0f, 1.0f, 0.0f);
    // start эта часть кода вычисляет время между кадрами, чтобы игрок двигался засчет времени
    newtime = clock();
    if (key_time) times = newtime - oldtime;
    else { // key_time нужен для того, чтобы при переключении из меню игры обратно в игру состояние times не увеличивалось
        times = 0;
        key_time = true;
    }
    oldtime = clock();
    // end эта часть кода вычисляет время между кадрами, чтобы игрок двигался засчет времени
    Draw_cubes();
    steve.update(times);
}
void game_menu() {
    world1.update();
    world2.update();
    world3.update();
    world4.update();

    if (exit_touch.update()) {
        exit(0);
    }

    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,
        0.0f, 1.0f, 0.0f);
    Draw_cubes();
    steve.update(0);
}