void game() {
    double times;
    gluLookAt(steve.PlayerX, steve.PlayerY + steve.h / 2, steve.PlayerZ,
        steve.PlayerX + lx, steve.PlayerY + ly + steve.h / 2, steve.PlayerZ + lz,
        0.0f, 1.0f, 0.0f);
    // start ��� ����� ���� ��������� ����� ����� �������, ����� ����� �������� ������ �������
    newtime = clock();
    if (key_time) times = newtime - oldtime;
    else { // key_time ����� ��� ����, ����� ��� ������������ �� ���� ���� ������� � ���� ��������� times �� �������������
        times = 0;
        key_time = true;
    }
    oldtime = clock();
    // end ��� ����� ���� ��������� ����� ����� �������, ����� ����� �������� ������ �������
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