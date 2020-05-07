class GUI_Menu {
public:
    float X1, Y1;                   /* .: */
    float x1= 0.1f,   y1 = 0.02f;  /* :. */ 
    float X2, Y2;                   /* :' */
    float x2 = -0.1f, y2 = -0.02f; /* ': */
    GLuint* tex;
    bool G = 0;
    GUI_Menu(GLuint* tex, float X1, float Y1, float X2, float Y2) {
        this->X1 = X1; this->Y1 = Y1;
        this->X2 = X2; this->Y2 = Y2;
        this->tex = tex;
    }
    void mouse(float x, float y) {
        x /= width / 2; y /= height / 2;
        x -= 1; y -= 1;
        x *= 0.36; y *= -0.2;
        if (x > x2 && x < x1 && y > y2 && y < y1) {
            G = 1;
        }
        else G = 0;

    }
    void update() {
        glBindTexture(GL_TEXTURE_2D, *tex);
        glBegin(GL_QUADS);
        glTexCoord2d(X1, Y2); glVertex3f(x1, y1, -0.2);
        glTexCoord2d(X1, Y1); glVertex3f(x1, y2, -0.2);
        glTexCoord2d(X2, Y1); glVertex3f(x2, y2, -0.2);
        glTexCoord2d(X2, Y2); glVertex3f(x2, y1, -0.2);
        glEnd();
        if (G) {
            glBindTexture(GL_TEXTURE_2D, *tex);
            glBegin(GL_QUADS);
            glTexCoord2d(X1, Y1); glVertex3f(x1, y1, -0.2);
            glTexCoord2d(X2, Y1); glVertex3f(x1, y2, -0.2);
            glTexCoord2d(X2, Y2); glVertex3f(x2, y2, -0.2);
            glTexCoord2d(X1, Y2); glVertex3f(x2, y1, -0.2);
            glEnd();
        }
    }
};
GUI_Menu g(&GUI_tex, 0, 0, 1, 1);