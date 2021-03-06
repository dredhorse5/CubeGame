/**
    \brief ��������� ��������
    ��������� �� ���� W � H ��������� �� int � ������� ����� �������� ������� ����������� - ������ � ������.

*/
void load_textures(const char* image, GLuint* texturesy, bool type) {
    unsigned char* top = SOIL_load_image(image, &W, &H, 0, SOIL_LOAD_RGBA); // ��������� �������� � soil
    glGenTextures(1, texturesy); // �������, ��� �������� �������� � ���������� Dirt, ����� ������ �������� � ��� �������� soil
    glBindTexture(GL_TEXTURE_2D, *texturesy); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (type) {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.8f);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, top); // ��������� �������� soil � ��������� dirt
    SOIL_free_image_data(top); // ����������� �������� �� soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void textures() {
    load_textures("textures/dirt.png", &dirt, 0);// ��������� ��������
    load_textures("textures/stone.png", &stone, 0);// ��������� ��������
    load_textures("textures/super_grass.png", &super_grass, 0);// ��������� ��������
    load_textures("textures/leaves.png", &leaves, 0);
    load_textures("textures/tree_oak.png", &tree_oak, 0);
    load_textures("textures/cobblestone.png", &cobblestone, 0);
    load_textures("textures/planks.png", &planks, 0);
    load_textures("textures/bricks.png", &bricks, 0);
    load_textures("textures/GUI.png", &GUI_tex, 1);

    load_textures("textures/icons/dirt.png", &dirt_icon_tex, 1);
    load_textures("textures/icons/stone.png", &stone_icon_tex, 1);
    load_textures("textures/icons/super_grass.png", &super_grass_icon_tex, 1);
    load_textures("textures/icons/leaves.png", &leaves_icon_tex, 1);
    load_textures("textures/icons/tree_oak.jpg", &tree_oak_icon_tex, 1);
    load_textures("textures/icons/cobblestone.png", &cobblestone_icon_tex, 1);
    load_textures("textures/icons/planks.png", &planks_icon_tex, 1);
    load_textures("textures/icons/bricks_icon.png", &bricks_icon_tex, 1);
	load_textures("textures/skybox.jpg", &skybox_tex, 1);
}

