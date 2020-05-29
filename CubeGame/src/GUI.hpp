/**
    /breaf класс для кнопки

    можно создать обьект кнопки
*/
class GUI_touch {

    float pix = 500.0f; // колличество пикселей по высоте и ширине в текстуре
    float X1 = 0 * 1/pix, Y1 = 0* 1/pix;            /* .: */  // для текстуры 
    float x1= 0.12f,   y1 = 0.022f;                 /* :. */ // для прямоугольника
    float X2 = 100.0f * 1/pix, Y2 = 20.0f * 1/pix;  /* :' */ // для текстуры
    float x2 = -0.12f, y2 = -0.022f;                /* ': */ // для прямоугольника
    GLuint* tex; // указатель на текстуру
    bool light = 0; // состояние подсветки кнопки
    bool click = 0; // состояние кнопки
public:
    GUI_touch(GLuint* tex, int X, int Y, int x, int y) {
        //текстура | смещение по текстуре на X | Y | смещение кнопки на экране по x | y
        X1 += 100 / pix * X; X2 += 100 / pix * X;
        Y1 += 20 / pix * Y; Y2 += 20 / pix * Y;
        
        x1 += x * 0.13; y1 += y * 0.03;
        x2 += x * 0.13; y2 += y * 0.03;
        this->tex = tex;
    }
    bool mouse(float x, float y, int click_status) {
        x /= W / 2; y /= H / 2;
        x -= 1; y -= 1;
        x *= 0.36; y *= -0.2;
        if (x > x2 && x < x1 && y > y2 && y < y1) {
            light = 1;
            click = click_status;
            return click_status;
        }
        else {
            light = 0;
            return 0;
        }
    }
    void update() {
        //std::cout << click;
        if (!light) {
            glBindTexture(GL_TEXTURE_2D, *tex);
            glBegin(GL_QUADS);
            glTexCoord2d(X2, Y1); glVertex3f(x1, y1, -0.2);
            glTexCoord2d(X2, Y2); glVertex3f(x1, y2, -0.2);
            glTexCoord2d(X1, Y2); glVertex3f(x2, y2, -0.2);
            glTexCoord2d(X1, Y1); glVertex3f(x2, y1, -0.2);
            glEnd();
        }
        else {
            glBindTexture(GL_TEXTURE_2D, *tex);
            glBegin(GL_QUADS);
            glTexCoord2d(X2, Y1 + 20 / pix); glVertex3f(x1, y1, -0.2);
            glTexCoord2d(X2, Y2 + 20 / pix); glVertex3f(x1, y2, -0.2);
            glTexCoord2d(X1, Y2 + 20 / pix); glVertex3f(x2, y2, -0.2);
            glTexCoord2d(X1, Y1 + 20 / pix); glVertex3f(x2, y1, -0.2);
            glEnd();
        }
    }
};
class GUI_background {
    float pix = 500.0f; // колличество пикселей по высоте и ширине в текстуре
    float X1 = 0.0f, Y1 = 0.0f;  /* .: */ // для текстуры 
    float x1 = 0.0f, y1 = 0.0f;  /* :. */ // для прямоугольника
    float X2 = 0.0f, Y2 = 0.0f;  /* :' */ // для текстуры
    float x2 = 0.0f, y2 = 0.0f;  /* ': */ // для прямоугольника
    float r = 1, g = 1, b = 1;
    bool tex_key = 1;
    GLuint *tex; // обычная текстура. создаем НЕ указатель из-за того, что мы можем не обьявить текстуру,
    //если бы мы не обьявили текстуру при указателе, то при бинде этой текстуры программа давала бы сбой
public:
    GUI_background(GLuint *tex, float X1, float Y1, float X2, float Y2, float x1, float y1, float x2, float y2, float light) {
        this->X1 = X1 / pix; this->X2 = X2 / pix;
        this->Y1 = Y1 / pix; this->Y2 = Y2 / pix;

        this->x1 = (x1 * 0.2); this->x2 = (x2 * 0.2);
        this->y1 = (y1 * 0.2); this->y2 = (y2 * 0.2);
        this->tex = tex;
        r = g = b = light;
    }
    GUI_background(float r, float g, float b, float x2, float y2, float x1, float y1) {
        this->r = r; this->g = g; this->b = b;
        this->x1 = (x1 * 0.2); this->x2 = (x2 * 0.2);
        this->y1 = (y1 * 0.2); this->y2 = (y2 * 0.2);
        tex_key = false;
    }
    void update() {
        if(tex_key)glBindTexture(GL_TEXTURE_2D, *tex);
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glTexCoord2d(X2, Y1); glVertex3f(x1, y1, -0.2);
        glTexCoord2d(X2, Y2); glVertex3f(x1, y2, -0.2);
        glTexCoord2d(X1, Y2); glVertex3f(x2, y2, -0.2);
        glTexCoord2d(X1, Y1); glVertex3f(x2, y1, -0.2);
        glEnd();

    }
};
class GUI_slider {
    float pix = 500.0f; // колличество пикселей по высоте и ширине в текстуре
    
    // задний фон
    float Gx1 = 0.0f, Gy1 = 0.0f;  /* :. */ // для прямоугольника
    float Gx2 = 0.0f, Gy2 = 0.0f;  /* ': */ // для прямоугольника
    float GX1 = 0,         GY1 = 200 / pix;
    float GX2 = 200 / pix, GY2 = 220 / pix;

    // ползунок
    float SX1 = 303 / pix, SY1 = 181 / pix;
    float SX2 = 311 / pix, SY2 = 199 / pix;
    float Sx1 = Gx2 + 0.05f, Sy1 = Gy2 + 0.1f;  /* :. */ // для прямоугольника

    // текст
    float Tx1 = 100 / pix, Ty1 = 1 / pix;
    float Tx2 = 165 / pix, Ty2 = 10 / pix;

    float Sx2 = Gx2, Sy2 = Gy2;  /* ': */ // для прямоугольника
public:
    bool click = 0;
    
    GUI_slider( float Gx1, float Gy1, float Gx2, float Gy2) {

        this->Gx1 = Gx1 ; this->Gx2 = Gx2;
        this->Gy1 = Gy1 ; this->Gy2 = Gy2;

        Sx1 = Gx2 / 2 + 0.02f; Sy1 = Gy2 + 0.042f;
        Sx2 = Gx2 / 2;         Sy2 = Gy2;       
    }
    void text_draw(int text) {
        glTexCoord2d(Tx2, Ty1); glVertex3f(Gx1 - 0.16, Gy1 - 0.01, -0.2);
        glTexCoord2d(Tx2, Ty2); glVertex3f(Gx1 - 0.16, Gy2 + 0.01, -0.2);
        glTexCoord2d(Tx1, Ty2); glVertex3f(Gx2 + 0.16, Gy2 + 0.01, -0.2);
        glTexCoord2d(Tx1, Ty1); glVertex3f(Gx2 + 0.16, Gy1 - 0.01, -0.2);
        
    }
    int mouse(float x, float y) { // возвращает значения от 6 до 100
        x /= W / 2; y /= H / 2;
        x -= 1; y -= 1;
        x *= 0.36; y *= -0.2;
        if (click) {
            Sx2 = x - 0.01f;
            Sx1 = x + 0.01f;
            if (Sx2 < Gx2){
                Sx2 = Gx2;
                Sx1 = Sx2 + 0.02f;
            }
            else if (Sx1 > Gx1) {
                Sx1 = Gx1;
                Sx2 = Sx1 - 0.02f;
            } 
        }
        
        return (((Sx1 + 0.05f) - Gx2) * (100 - 6) / (Gx1 - Gx2) - 6 );
    }
    void click_status(float x, float y) {
        x /= W / 2; y /= H / 2;
        x -= 1; y -= 1;
        x *= 0.36; y *= -0.2;
        if (x > Gx2 && x < Gx1 && y  > Gy2 && y < Gy1){
            click = 1;
            Sx2 = x - 0.01f;
            Sx1 = x + 0.01f;
        }
    }
    void update() {
        glBindTexture(GL_TEXTURE_2D, GUI_tex);
        glBegin(GL_QUADS);

        text_draw(visible_range);

        glTexCoord2d(SX2, SY1); glVertex3f(Sx1, Sy1, -0.2);
        glTexCoord2d(SX2, SY2); glVertex3f(Sx1, Sy2, -0.2);
        glTexCoord2d(SX1, SY2); glVertex3f(Sx2, Sy2, -0.2);
        glTexCoord2d(SX1, SY1); glVertex3f(Sx2, Sy1, -0.2);

        glTexCoord2d(GX2, GY1); glVertex3f(Gx1, Gy1, -0.2);
        glTexCoord2d(GX2, GY2); glVertex3f(Gx1, Gy2, -0.2);
        glTexCoord2d(GX1, GY2); glVertex3f(Gx2, Gy2, -0.2);
        glTexCoord2d(GX1, GY1); glVertex3f(Gx2, Gy1, -0.2);

        glEnd();

    }
};
GUI_touch world1(&GUI_tex, 0,0, 1, 1 );
GUI_touch world2(&GUI_tex, 0,2, -1, 1);
GUI_touch world3(&GUI_tex, 0,4, 1, -1);
GUI_touch world4(&GUI_tex, 0,6, -1, -1);
GUI_touch exit_touch(&GUI_tex, 1, 6, -1, -3);
GUI_touch exit_and_save(&GUI_tex, 1, 4, 1, -3);
GUI_slider slider(0.25, 0.112, -0.25, 0.07);
// y край 1
// x край 1.78
GUI_background hotbar(&GUI_tex, 200, 200, 382, 222, 1, -0.76, -1, -1, 1);
GUI_background aim(&GUI_tex, 24, 220, 48, 244, 0.05, 0.05, -0.05, -0.05 , 1);
GUI_background background_main_menu(&dirt, 0, 0, 8000, 5000, 1.78, 1, -1.78, -1, 0.5);
GUI_background save_icon(&GUI_tex, 156, 22, 170, 36, 0.15, 0.15, -0.15, -0.15, 1);
GUI_background icon_selecter(&GUI_tex, 0, 220, 24, 244, 0.13, 0.13, -0.13, -0.13, 1);

GUI_background dirt_icon        (&dirt_icon_tex,        0, 0, 500, 500, 0.08, 0.08, -0.08, -0.08, 1);
GUI_background stone_icon       (&stone_icon_tex,       0, 0, 500, 500, 0.08, 0.08, -0.08, -0.08, 1);
GUI_background super_grass_icon (&super_grass_icon_tex, 0, 0, 500, 500, 0.08, 0.08, -0.08, -0.08, 1);
GUI_background tree_oak_icon    (&tree_oak_icon_tex,    0, 0, 500, 500, 0.08, 0.08, -0.08, -0.08, 1);
GUI_background leaves_icon      (&leaves_icon_tex,      0, 0, 500, 500, 0.08, 0.08, -0.08, -0.08, 1);
GUI_background cobblestone_icon (&cobblestone_icon_tex, 0, 0, 500, 500, 0.08, 0.08, -0.08, -0.08, 1);
GUI_background planks_icon      (&planks_icon_tex,      0, 0, 500, 500, 0.08, 0.08, -0.08, -0.08, 1);
GUI_background bricks_icon      (&bricks_icon_tex,      0, 0, 500, 500, 0.08, 0.08, -0.08, -0.08, 1);
//class GUI_touch1 {
//    int pix = 500;
//    float X1 = 0, Y1 = 0;/* .: */ // для текстуры 
//    float x1 = 0, y1 = 0;/* :. */ // для прямоугольника
//    float X2 = 0, Y2 = 0;/* :' */ // для текстуры
//    float x2 = 0, y2 = 0;/* ': */ // для прямоугольника
//    GLuint* tex; // указатель на текстуру
//    bool light = 0; // состояние подсветки кнопки
//    bool click = 0; // состояние кнопки
//public:
//    /*
//    GLuint* tex - указатель на текстуру,
//    int pix- высота текстуры
//    int X - x координата правого нижнего угла используемого куска текстуры
//    int Y - y координата правого нижнего угла используемого куска текстуры
//    float x1, float y1 - координаты правого верхнего угла прямоугольника, который будет рисоваться
//    float x2, float y2 - координаты левого нижнего угла прямоугольника, который будет рисоваться
//    */
//    GUI_touch1(GLuint* tex, int pix, float X, float Y, float x1, float y1, float x2, float y2) {
//        X2 = X/pix;
//        Y2 = Y/pix;
//
//        this->x1 = x1; this->x2 = x2;
//        this->y1 = y1; this->y2 = y2;
//
//        this->tex = tex;
//        this->pix = pix;
//    }
//    /**
//        /brief функция обработки мыши
//
//        вызывается в функиях, где брабатывается мышка. в зависимости от функции(функция нажатия или функция движения мыши)
//        мы передаем статус клика. если же мы в эту функцию передаем нажатие кнопки единицу, то она возвращает 1 и
//        дальше мы уже можем определять, что делать.
//
//        x - координата мыши по оси x
//        y - координата мыши по оси y
//        click_status - передаем, нажата ли кнопка мыши
//
//    */
//    bool mouse(float x, float y, int click_status) {
//        // изменяем координаты мыши. изначально ее координаты определяются как высота и ширина в пикселях,
//        // но координаты кнопки в других значениях - к ним и приводим
//        x /= W / 2; y /= H / 2; 
//        x -= 1; y -= 1;
//        x *= 0.36; y *= -0.2;
//        // смотрим, попадает ли мышка в кнопку
//        if (x > x2 && x < x1 && y > y2 && y < y1) {
//            light = 1; // включаем подсветку
//            click = click_status; // передаем, нажата ли мышка
//            return click_status; // возвращаем клик. если мы нажали, то можно сравнить эту функцию там, где мы ее вызываем
//            // и дальше уже задавать поведение. эта функция равна 1 - что-то печатаем или делаем
//        }
//        else {
//            light = 0; // не подсвечиваем
//            return 0;
//        }
//    }
//    /**
//        /brief рисуем кнопку. эта функция вызывается ДО glulookat и в функции, отвечающая за рисование.
//    */
//    void update() {
//        glBindTexture(GL_TEXTURE_2D, *tex);
//        glBegin(GL_QUADS);
//        if (!light) {
//            glTexCoord2d(X2, Y1); glVertex3f(x1, y1, -0.2);
//            glTexCoord2d(X2, Y2); glVertex3f(x1, y2, -0.2);
//            glTexCoord2d(X1, Y2); glVertex3f(x2, y2, -0.2);
//            glTexCoord2d(X1, Y1); glVertex3f(x2, y1, -0.2);
//        }
//        else {
//            glTexCoord2d(X2, Y1 * 2); glVertex3f(x1, y1, -0.2);
//            glTexCoord2d(X2, Y2 * 2); glVertex3f(x1, y2, -0.2);
//            glTexCoord2d(X1, Y2 * 2); glVertex3f(x2, y2, -0.2);
//            glTexCoord2d(X1, Y1 * 2); glVertex3f(x2, y1, -0.2);
//        }
//        glEnd();
//    }
//};
//class GUI_background1 {
//    float pix = 500.0f; // колличество пикселей по высоте и ширине в текстуре
//    float X1 = 0.0f, Y1 = 0.0f;  /* .: */ // для текстуры 
//    float x1 = 0.0f, y1 = 0.0f;  /* :. */ // для прямоугольника
//    float X2 = 0.0f, Y2 = 0.0f;  /* :' */ // для текстуры
//    float x2 = 0.0f, y2 = 0.0f;  /* ': */ // для прямоугольника
//    GLuint* tex; 
//    bool key = 1; // состояние текстуры- она есть или нет
//public:
//    /**
//        /brief конструктор класса, где мы можем задать все границы для текстуры и прямоугольника
//
//        GLuint* tex - указатель на текстуру,
//        int pix- высота текстуры
//        int X2 - x координата правого нижнего угла используемого куска текстуры
//        int Y2 - y координата правого нижнего угла используемого куска текстуры
//        float x1, float y1 - координаты правого верхнего угла прямоугольника, который будет рисоваться
//        float x2, float y2 - координаты левого нижнего угла прямоугольника, который будет рисоваться
//    */
//    GUI_background1(GLuint* tex, int pix, float X2, float Y2, float x1, float y1, float x2, float y2) {
//        this->X2 = X2 / pix;
//        this->Y2 = Y2 / pix;
//
//        this->x1 = (x1 * 0.2); this->x2 = (x2 * 0.2);
//        this->y1 = (y1 * 0.2); this->y2 = (y2 * 0.2);
//        this->tex = tex;
//        this->pix = pix;
//    }
//    /**
//        /brief конструктор класса, где мы можем задать все границы для прямоугольника без текстуры
//
//        float x1, float y1 - координаты правого верхнего угла прямоугольника, который будет рисоваться
//        float x2, float y2 - координаты левого нижнего угла прямоугольника, который будет рисоваться
//    */
//    GUI_background1(float x2, float y2, float x1, float y1) {
//        this->x1 = (x1 * 0.2); this->x2 = (x2 * 0.2);
//        this->y1 = (y1 * 0.2); this->y2 = (y2 * 0.2);
//        key = 0; // если вызываем этот конструктор, то 
//    }
//    void update() {
//        if(key)glBindTexture(GL_TEXTURE_2D, *tex);  //  если нет текстуры- не биндим ее
//        else glBindTexture(GL_TEXTURE_2D, GLU_NONE); // а биндим ничего.пустоту. дыру
//
//        glBegin(GL_QUADS);
//        glTexCoord2d(X2, Y1); glVertex3f(x1, y1, -0.2);
//        glTexCoord2d(X2, Y2); glVertex3f(x1, y2, -0.2);
//        glTexCoord2d(X1, Y2); glVertex3f(x2, y2, -0.2);
//        glTexCoord2d(X1, Y1); glVertex3f(x2, y1, -0.2);
//        glEnd();
//
//    }
//};
//class GUI_slider1 {
//    float pix = 500.0f; // колличество пикселей по высоте и ширине в текстуре
//
//    // задний фон
//    float Gx1 = 0.0f, Gy1 = 0.0f;  /* :. */ // для прямоугольника
//    float Gx2 = 0.0f, Gy2 = 0.0f;  /* ': */ // для прямоугольника
//    float GX1 = 0, GY1 = 200 / pix;
//    float GX2 = 200 / pix, GY2 = 220 / pix;
//
//    // ползунок
//    float SX1 = 303 / pix, SY1 = 181 / pix;
//    float SX2 = 311 / pix, SY2 = 199 / pix;
//    float Sx1 = Gx2 + 0.05f, Sy1 = Gy2 + 0.1f;  /* :. */ // для прямоугольника
//
//    // текст
//    float Tx1 = 100 / pix, Ty1 = 1 / pix;
//    float Tx2 = 165 / pix, Ty2 = 10 / pix;
//
//    float Sx2 = Gx2, Sy2 = Gy2;  /* ': */ // для прямоугольника
//public:
//    bool click = 0;
//
//    GUI_slider1(float Gx1, float Gy1, float Gx2, float Gy2) {
//
//        this->Gx1 = Gx1; this->Gx2 = Gx2;
//        this->Gy1 = Gy1; this->Gy2 = Gy2;
//
//        Sx1 = Gx2 / 2 + 0.02f; Sy1 = Gy2 + 0.042f;
//        Sx2 = Gx2 / 2;         Sy2 = Gy2;
//    }
//    void text_draw(int text) {
//        glTexCoord2d(Tx2, Ty1); glVertex3f(Gx1 - 0.16, Gy1 - 0.01, -0.2);
//        glTexCoord2d(Tx2, Ty2); glVertex3f(Gx1 - 0.16, Gy2 + 0.01, -0.2);
//        glTexCoord2d(Tx1, Ty2); glVertex3f(Gx2 + 0.16, Gy2 + 0.01, -0.2);
//        glTexCoord2d(Tx1, Ty1); glVertex3f(Gx2 + 0.16, Gy1 - 0.01, -0.2);
//
//    }
//    int mouse(float x, float y) { // возвращает значения от 6 до 100
//        x /= W / 2; y /= H / 2;
//        x -= 1; y -= 1;
//        x *= 0.36; y *= -0.2;
//        if (click) {
//            Sx2 = x - 0.01f;
//            Sx1 = x + 0.01f;
//            if (Sx2 < Gx2) {
//                Sx2 = Gx2;
//                Sx1 = Sx2 + 0.02f;
//            }
//            else if (Sx1 > Gx1) {
//                Sx1 = Gx1;
//                Sx2 = Sx1 - 0.02f;
//            }
//        }
//
//        return (((Sx1 + 0.05f) - Gx2) * (100 - 6) / (Gx1 - Gx2) - 6);
//    }
//    void click_status(float x, float y) {
//        x /= W / 2; y /= H / 2;
//        x -= 1; y -= 1;
//        x *= 0.36; y *= -0.2;
//        if (x > Gx2 && x < Gx1 && y  > Gy2 && y < Gy1) {
//            click = 1;
//            Sx2 = x - 0.01f;
//            Sx1 = x + 0.01f;
//        }
//    }
//    void update() {
//        glBindTexture(GL_TEXTURE_2D, GUI_tex);
//        glBegin(GL_QUADS);
//
//        text_draw(visible_range);
//
//        glTexCoord2d(SX2, SY1); glVertex3f(Sx1, Sy1, -0.2);
//        glTexCoord2d(SX2, SY2); glVertex3f(Sx1, Sy2, -0.2);
//        glTexCoord2d(SX1, SY2); glVertex3f(Sx2, Sy2, -0.2);
//        glTexCoord2d(SX1, SY1); glVertex3f(Sx2, Sy1, -0.2);
//
//        glTexCoord2d(GX2, GY1); glVertex3f(Gx1, Gy1, -0.2);
//        glTexCoord2d(GX2, GY2); glVertex3f(Gx1, Gy2, -0.2);
//        glTexCoord2d(GX1, GY2); glVertex3f(Gx2, Gy2, -0.2);
//        glTexCoord2d(GX1, GY1); glVertex3f(Gx2, Gy1, -0.2);
//
//        glEnd();
//
//    }
//};
//class area {
//    float x1, x2;
//    float y1, y2;
//public:
//    area(float x1, float y1, float x2, float y2) {
//        this->x1 = x1; this->x2 = x2;
//        this->y1 = y1; this->y2 = y2;
//    }
//    //
//    // *   ----1 точка
//    //   * --------2 точка
//    //
//    bool update() {
//        if (x1 < steve.PlayerX && x2 > steve.PlayerX && y1 < steve.PlayerY && y2 > steve.PlayerY)
//            return true;
//        else return false;
//    }
//};