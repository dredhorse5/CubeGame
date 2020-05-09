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
        X1 += 100 * 1 / pix * X; X2 += 100 * 1 / pix * X;
        Y1 += 20 * 1 / pix * Y; Y2 += 20 * 1 / pix * Y;
        
        x1 += x * 0.13; y1 += y * 0.03;
        x2 += x * 0.13; y2 += y * 0.03;
        this->tex = tex;
    }
    void mouse(float x, float y, int click_status) {
        x /= width / 2; y /= height / 2;
        x -= 1; y -= 1;
        x *= 0.36; y *= -0.2;
        if (x > x2 && x < x1 && y > y2 && y < y1) {
            light = 1;
            click_status = click;
        }
        else {
            light = 0;
            click = 0;
        }
    }
    bool update() {
        glBindTexture(GL_TEXTURE_2D, *tex);
        glBegin(GL_QUADS);
        glTexCoord2d(X2, Y1); glVertex3f(x1, y1, -0.2);
        glTexCoord2d(X2, Y2); glVertex3f(x1, y2, -0.2);
        glTexCoord2d(X1, Y2); glVertex3f(x2, y2, -0.2);
        glTexCoord2d(X1, Y1); glVertex3f(x2, y1, -0.2);
        glEnd();
        if (light) {
            glBindTexture(GL_TEXTURE_2D, *tex);
            glBegin(GL_QUADS);
            glTexCoord2d(X2, Y1); glVertex3f(x1, y1, -0.2);
            glTexCoord2d(X2, Y2); glVertex3f(x1, y2, -0.2);
            glTexCoord2d(X1, Y2); glVertex3f(x2, y2, -0.2);
            glTexCoord2d(X1, Y1); glVertex3f(x2, y1, -0.2);
            glEnd();
        }
        return false;
    }
};
class GUI_background {
    float pix = 500.0f; // колличество пикселей по высоте и ширине в текстуре
    float X1 = 0.0f, Y1 = 0.0f;  /* .: */ // для текстуры 
    float x1 = 0.0f, y1 = 0.0f;  /* :. */ // для прямоугольника
    float X2 = 0.0f, Y2 = 0.0f;  /* :' */ // для текстуры
    float x2 = 0.0f, y2 = 0.0f;  /* ': */ // для прямоугольника
    float r = 1, g = 1, b = 1;
    GLuint tex; // обычная текстура. создаем НЕ указатель из-за того, что мы можем не обьявить текстуру,
    //если бы мы не обьявили текстуру при указателе, то при бинде этой текстуры программа давала бы сбой
public:
    GUI_background(GLuint tex, float X1, float Y1, float X2, float Y2, float x1, float y1, float x2, float y2) {
        this->X1 = X1 / pix; this->X2 = X2 / pix;
        this->Y1 = Y1 / pix; this->Y2 = Y2 / pix;

        this->x1 = x1; this->x2 = x2;
        this->y1 = y1; this->y2 = y2;
        this->tex = tex;
    }
    GUI_background(float r, float g, float b, float x1, float y1, float x2, float y2) {
        this->r = r; this->g = g; this->b = b;
        this->x1 = x1; this->x2 = x2;
        this->y1 = y1; this->y2 = y2;
    }
    void update() {
        glBindTexture(GL_TEXTURE_2D, tex);
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glTexCoord2d(X2, Y1); glVertex3f(x1, y1, -0.2);
        glTexCoord2d(X2, Y2); glVertex3f(x1, y2, -0.2);
        glTexCoord2d(X1, Y2); glVertex3f(x2, y2, -0.2);
        glTexCoord2d(X1, Y1); glVertex3f(x2, y1, -0.2);
        glEnd();

    }
};
GUI_touch g(&GUI_tex, 0,0, 1, 1 );
GUI_touch gy(&GUI_tex, 0,2, -1, 1);
GUI_touch gys(&GUI_tex, 0,4, 1, -1);
GUI_touch gysa(&GUI_tex, 0,6, -1, -1);

GUI_background f(1, 1, 1, -0.1, -0.1, 0.1, 0.1);