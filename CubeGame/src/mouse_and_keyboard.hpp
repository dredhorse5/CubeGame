
/**
	\brief определяет НАЖАТИЕ клавиш клавиатуры

	вызывается при НАЖАТОЙ кнопки клавиатуры

	\param[in] key передает ASCII код нажатой клавиши
	\param[in] x положение курсора мыши при нажатии клавиши по оси x
	\param[in] y положение курсора мыши при нажатии клавиши по оси y

*/
void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
if (game_now == GAME) {
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	game_now = GAME_MENU;
}
else if (game_now == GAME_MENU) {
	game_now = GAME;
	glutSetCursor(GLUT_CURSOR_NONE);
	oldtime = clock(); // обновляем старое время, чтобы игрок не улетел
}
break;
if (game_now == GAME) {
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
	case 'R':
	case 'r':
		IDblocks++;
		if (IDblocks > blocks) IDblocks = 0;
		break;

	case'f':
	case'F':
		IDblocks--;
		if (IDblocks < 0) IDblocks = blocks;
		break;

}
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
		if (game_now == GAME) {
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
}
/**
	\brief обрабатывает нажатие мыши

	\param[in] button определяет, какая именно кнопка нажата- правая, левая или средняя
	\param[in] state состояние этой кнопки - нажата или разжата
	\param[in] x координата x, где произошло нажатие на кнопку
	\param[in] y координата y, где произошло нажатие на кнопку

*/
void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		switch (state) {
		case GLUT_DOWN:		//Если нажата
			if (game_now == GAME) mLeft = true;
			else if (game_now == GAME_MENU) {
				world1.mouse(x, y, 1);
				world2.mouse(x, y, 1);
				world3.mouse(x, y, 1);
				world4.mouse(x, y, 1);
				exit_and_save.mouse(x, y, 1);
				if (exit_touch.mouse(x, y, 1)) game_now = MAIN_MENU;
				slider.click_status(x, y);
			}
			else if (game_now == MAIN_MENU) {
				if (world1.mouse(x, y, 1)) {
					world_now = 1;
					game_now = GAME;
					load_game();
					glutSetCursor(GLUT_CURSOR_NONE);
				}
				else if (world2.mouse(x, y, 1)) {
					world_now = 2;
					game_now = GAME;
					load_game();
					glutSetCursor(GLUT_CURSOR_NONE);
				}
				else if (world3.mouse(x, y, 1)) {
					world_now = 3;
					game_now = GAME;
					load_game();
					glutSetCursor(GLUT_CURSOR_NONE);
				}
				else if (world4.mouse(x, y, 1)) {
					world_now = 4;
					game_now = GAME;
					load_game();
					glutSetCursor(GLUT_CURSOR_NONE);
				}
				else if (exit_touch.mouse(x, y, 1)) exit(0);
			}
			break;
		case GLUT_UP:      // если опущена
			mLeft = false;
			slider.click = false;
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
	\brief мониторит координаты мыши в окне

	функция вызывается при изменении координат мыши, и соотвественно передает их. используется в данном случае для изменения
	угла поворота камеры

*/
void mouseMove(int x, int y) {
	if (game_now == GAME) {
		if (mouseXOld != 0 || mouseYOld != 0) {
			angleX -= mouseXOld * 0.001f;
			angleY -= mouseYOld * 0.001f;

			if (angleY > 3.14 / 2) angleY = 3.14 / 2;
			if (angleY < -3.14 / 2) angleY = -3.14 / 2;

			mouseXOld = 0; mouseYOld = 0;

			// update camera's direction
			lx = float(sin(angleX));
			lz = float(-cos(angleX));
			ly = float(-tan(angleY));
		}
		else {
			mouseXOld = (width / 2) - x;
			mouseYOld = (height / 2) - y;
			glutWarpPointer((width / 2), (height / 2));
		}
	}
	else if (game_now == GAME_MENU) {
		exit_touch.mouse(x, y, 0);
		exit_and_save.mouse(x, y, 0);
		visible_range = slider.mouse(x, y);
	}
	else if (game_now == MAIN_MENU) {
		world1.mouse(x, y, 0);
		world2.mouse(x, y, 0);
		world3.mouse(x, y, 0);
		world4.mouse(x, y, 0);
		exit_touch.mouse(x, y, 0);
	}
}