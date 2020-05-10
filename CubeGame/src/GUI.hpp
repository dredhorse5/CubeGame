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
        x /= width / 2; y /= height / 2;
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
    GUI_background(GLuint *tex, float X1, float Y1, float X2, float Y2, float x1, float y1, float x2, float y2) {
        this->X1 = X1 / pix; this->X2 = X2 / pix;
        this->Y1 = Y1 / pix; this->Y2 = Y2 / pix;

        this->x1 = (x1 * 0.2); this->x2 = (x2 * 0.2);
        this->y1 = (y1 * 0.2); this->y2 = (y2 * 0.2);
        this->tex = tex;
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
GUI_touch world1(&GUI_tex, 0,0, 1, 1 );
GUI_touch world2(&GUI_tex, 0,2, -1, 1);
GUI_touch world3(&GUI_tex, 0,4, 1, -1);
GUI_touch world4(&GUI_tex, 0,6, -1, -1);
GUI_touch exit_touch(&GUI_tex, 1, 6, -1, -3);
// y край 1
// x край 1.78
GUI_background hotbar(&GUI_tex, 200, 200, 382, 222, 1, -0.76, -1, -1);
GUI_background aim(&GUI_tex, 24, 220, 48, 244, 0.05, 0.05, -0.05, -0.05);