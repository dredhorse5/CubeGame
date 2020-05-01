void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		switch (state) {
		case GLUT_DOWN:		//Если нажата
			mLeft = true;
			break;
		case GLUT_UP:      // если опущена
			mLeft = false;
			break;
		}
	}

	if (button == GLUT_RIGHT_BUTTON) {
		switch (state) {
		case GLUT_DOWN:		//Если нажата
			mRight = true;
			break;
		case GLUT_UP:      // если опущена
			mRight = false;
			break;
		}
	}

}
/**
	\brief определяет НАЖАТИЕ клавиш клавиатуры

	вызывается при НАЖАТОЙ кнопки клавиатуры

	\param[in] key передает ASCII код нажатой клавиши
	\param[in] x положение курсора мыши при нажатии клавиши по оси x
	\param[in] y положение курсора мыши при нажатии клавиши по оси y

*/





void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // если клавиша esc(27) нажата, то выходим из программы
		exit(0);
	case 'W':
	case 'w':
		KeyFront = 1;
		break;
	case 'S':
	case 's':
		KeyFront = -1;
		break;
	case 'D':
	case 'd':
		KeySide = 1;
		break;
	case 'A':
	case 'a':
		KeySide = -1;
		break;
	case 32:
		steve.jump();
		break;
	}
}
/**
	\brief определяет ОТЖАТИЕ клавиш клавиатуры

	вызывается при ОТЖАТОЙ кнопки клавиатуры

	\param[in] key передает ASCII код нажатой клавиши
	\param[in] x положение курсора мыши при отжатии клавиши по оси x
	\param[in] y положение курсора мыши при отжатии клавиши по оси y

*/



void processNormalKeysUP(unsigned char key, int x, int y) {
	switch (key) {
	case 'W':
	case 'w':
		KeyFront = 0;
		break;
	case 'S':
	case 's':
		KeyFront = 0;
		break;
	case 'D':
	case 'd':
		KeySide = 0;
		break;
	case 'A':
	case 'a':
		KeySide = 0;
		break;
	}
}



/**
	\brief рисует куб

	эта функция рисует куб

*/