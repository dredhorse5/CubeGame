
/**
	\brief ���������� ������� ������ ����������

	���������� ��� ������� ������ ����������

	\param[in] key �������� ASCII ��� ������� �������
	\param[in] x ��������� ������� ���� ��� ������� ������� �� ��� x
	\param[in] y ��������� ������� ���� ��� ������� ������� �� ��� y

*/
void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		if (game_now == GAME) game_now = GAME_MENU;
		else if (game_now == GAME_MENU) game_now = GAME;
		key_time = false;
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
		}
	}
}
/**
	\brief ���������� ������� ������ ����������

	���������� ��� ������� ������ ����������

	\param[in] key �������� ASCII ��� ������� �������
	\param[in] x ��������� ������� ���� ��� ������� ������� �� ��� x
	\param[in] y ��������� ������� ���� ��� ������� ������� �� ��� y

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
	\brief ������������ ������� ����

	\param[in] button ����������, ����� ������ ������ ������- ������, ����� ��� �������
	\param[in] state ��������� ���� ������ - ������ ��� �������
	\param[in] x ���������� x, ��� ��������� ������� �� ������
	\param[in] y ���������� y, ��� ��������� ������� �� ������

*/
void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		switch (state) {
		case GLUT_DOWN:		//���� ������
			if (game_now == GAME) mLeft = true;
			else if (game_now == GAME_MENU) {
				world1.mouse(x, y, 1);
				world2.mouse(x, y, 1);
				world3.mouse(x, y, 1);
				world4.mouse(x, y, 1);
				exit_touch.mouse(x, y, 1);
			}
			break;
		case GLUT_UP:      // ���� �������
			mLeft = false;
			break;
		}
		
	}

	if (button == GLUT_RIGHT_BUTTON) {
		switch (state) {
		case GLUT_DOWN:		//���� ������
			mRight = true;
			break;
		case GLUT_UP:      // ���� �������
			mRight = false;
			break;
		}
	}

}
/**
	\brief ��������� ���������� ���� � ����

	������� ���������� ��� ��������� ��������� ����, � ������������� �������� ��. ������������ � ������ ������ ��� ���������
	���� �������� ������

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
		world1.mouse(x, y, 0);
		world2.mouse(x, y, 0);
		world3.mouse(x, y, 0);
		world4.mouse(x, y, 0);
		exit_touch.mouse(x, y, 0);
	}
}