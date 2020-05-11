/**
    \brief загружает текстуры
    принимает на вход W и H указатели на int в которые будут помещены размеры изображения - высота и ширина.

*/
void load_textures(const char* image, GLuint* texturesy, bool type) {
    unsigned char* top = SOIL_load_image(image, &W, &H, 0, SOIL_LOAD_RGBA); // загружаем текстуру в soil
    glGenTextures(1, texturesy); // говорим, что начинаем работать с переменной Dirt, чтобы дальше записать в нее текстуру soil
    glBindTexture(GL_TEXTURE_2D, *texturesy); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (type) {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.8f);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, top); // загружаем текстуру soil в перменную dirt
    SOIL_free_image_data(top); // освобождаем текстуру из soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void textures() {
    load_textures("textures/dirt.png", &dirt, 0);// загружаем текстуру
    load_textures("textures/stone.png", &stone, 0);// загружаем текстуру
    load_textures("textures/super_grass.png", &super_grass, 0);// загружаем текстуру
    load_textures("textures/leaves.png", &leaves, 0);
    load_textures("textures/tree_oak.png", &tree_oak, 0);
    load_textures("textures/GUI.png", &GUI_tex, 1);
}