class GUI_touch {

    float pix = 500.0f; // ����������� �������� �� ������ � ������ � ��������
    float X1 = 0 * 1/pix, Y1 = 0* 1/pix;            /* .: */  // ��� �������� 
    float x1= 0.12f,   y1 = 0.022f;                 /* :. */ // ��� ��������������
    float X2 = 100.0f * 1/pix, Y2 = 20.0f * 1/pix;  /* :' */ // ��� ��������
    float x2 = -0.12f, y2 = -0.022f;                /* ': */ // ��� ��������������
    GLuint* tex; // ��������� �� ��������
    bool light = 0; // ��������� ��������� ������
    bool click = 0; // ��������� ������
public:
    GUI_touch(GLuint* tex, int X, int Y, int x, int y) {
        //�������� | �������� �� �������� �� X | Y | �������� ������ �� ������ �� x | y
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
    float pix = 500.0f; // ����������� �������� �� ������ � ������ � ��������
    float X1 = 0.0f, Y1 = 0.0f;  /* .: */ // ��� �������� 
    float x1 = 0.0f, y1 = 0.0f;  /* :. */ // ��� ��������������
    float X2 = 0.0f, Y2 = 0.0f;  /* :' */ // ��� ��������
    float x2 = 0.0f, y2 = 0.0f;  /* ': */ // ��� ��������������
    float r = 1, g = 1, b = 1;
    bool tex_key = 1;
    GLuint *tex; // ������� ��������. ������� �� ��������� ��-�� ����, ��� �� ����� �� �������� ��������,
    //���� �� �� �� �������� �������� ��� ���������, �� ��� ����� ���� �������� ��������� ������ �� ����
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
class GUI_slider {
    float pix = 500.0f; // ����������� �������� �� ������ � ������ � ��������
    // ������ ���
    float Gx1 = 0.0f, Gy1 = 0.0f;  /* :. */ // ��� ��������������
    float Gx2 = 0.0f, Gy2 = 0.0f;  /* ': */ // ��� ��������������
    float GX1 = 0,         GY1 = 200 / pix;
    float GX2 = 200 / pix, GY2 = 220 / pix;

    // ��������
    float SX1 = 303 / pix, SY1 = 181 / pix;
    float SX2 = 311 / pix, SY2 = 199 / pix;
    float Sx1 = Gx2 + 0.05f, Sy1 = Gy2 + 0.1f;  /* :. */ // ��� ��������������
    float Sx2 = Gx2, Sy2 = Gy2;  /* ': */ // ��� ��������������
public:
    bool click = 0;
    
    GUI_slider( float Gx1, float Gy1, float Gx2, float Gy2) {

        this->Gx1 = Gx1 ; this->Gx2 = Gx2;
        this->Gy1 = Gy1 ; this->Gy2 = Gy2;

        Sx1 = Gx2 + 0.02f; Sy1 = Gy2 + 0.042f;  
        Sx2 = Gx2;         Sy2 = Gy2;       
    }
    int mouse(float x, float y) { // ���������� �������� �� 6 �� 100
        x /= width / 2; y /= height / 2;
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
        x /= width / 2; y /= height / 2;
        x -= 1; y -= 1;
        x *= 0.36; y *= -0.2;
        if (x > Sx2 && x < Sx1 && y  > Sy2 && y < Sy1)  click = 1;
    }
    void update() {
        glBindTexture(GL_TEXTURE_2D, GUI_tex);
        glBegin(GL_QUADS);
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
// y ���� 1
// x ���� 1.78
GUI_background hotbar(&GUI_tex, 200, 200, 382, 222, 1, -0.76, -1, -1);
GUI_background aim(&GUI_tex, 24, 220, 48, 244, 0.05, 0.05, -0.05, -0.05);
GUI_slider slider(0.25, 0.112, -0.25, 0.07);