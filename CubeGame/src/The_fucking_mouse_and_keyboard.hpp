void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		switch (state) {
		case GLUT_DOWN:		//���� ������
			mLeft = true;
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
	\brief ���������� ������� ������ ����������

	���������� ��� ������� ������ ����������

	\param[in] key �������� ASCII ��� ������� �������
	\param[in] x ��������� ������� ���� ��� ������� ������� �� ��� x
	\param[in] y ��������� ������� ���� ��� ������� ������� �� ��� y

*/





void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ���� ������� esc(27) ������, �� ������� �� ���������
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
	\brief ���������� ������� ������ ����������

	���������� ��� ������� ������ ����������

	\param[in] key �������� ASCII ��� ������� �������
	\param[in] x ��������� ������� ���� ��� ������� ������� �� ��� x
	\param[in] y ��������� ������� ���� ��� ������� ������� �� ��� y

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
	\brief ������ ���

	��� ������� ������ ���

*/