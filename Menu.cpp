#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "Menu.h"

Menu::Menu()
{
	roundnum2[0] = 51;
	roundnum2[1] = 48;
}

char Menu::checkkey(int key)//help function used to check the input key
{
	switch (key)
	{
	case FSKEY_A:
		return 'A';
	case FSKEY_B:
		return 'B';
	case FSKEY_C:
		return 'C';
	case FSKEY_D:
		return 'D';
	case FSKEY_E:
		return 'E';
	case FSKEY_F:
		return 'F';
	case FSKEY_G:
		return 'G';
	case FSKEY_H:
		return 'H';
	case FSKEY_I:
		return 'I';
	case FSKEY_J:
		return 'J';
	case FSKEY_K:
		return 'K';
	case FSKEY_L:
		return 'L';
	case FSKEY_M:
		return 'M';
	case FSKEY_N:
		return 'N';
	case FSKEY_O:
		return 'O';
	case FSKEY_P:
		return 'P';
	case FSKEY_Q:
		return 'Q';
	case FSKEY_R:
		return 'R';
	case FSKEY_S:
		return 'S';
	case FSKEY_T:
		return 'T';
	case FSKEY_U:
		return 'U';
	case FSKEY_V:
		return 'V';
	case FSKEY_W:
		return 'W';
	case FSKEY_X:
		return 'X';
	case FSKEY_Y:
		return 'Y';
	case FSKEY_Z:
		return 'Z';
	}
	return '0';
}

void Menu::Type(int key, player& gameplayer1, player& gameplayer2)
{
	if (show_name1 == 1)
	{
		if (key == FSKEY_ENTER)
		{
			show_name1 = 0;
			gameplayer1.set_name(result);
		}
		else if (key == FSKEY_BS)
		{
			if (counter1 > 0)
			{
				counter1--;
				result[counter1] = 0;
			}
		}
		else if (key != FSKEY_NULL)
		{
			if (5 >= counter1 && '0' != checkkey(key))
			{
				result[counter1] = checkkey(key);
				counter1++;
			}
		}
		glColor3f(255, 0, 0);
		glRasterPos2i(450, 245);
		YsGlDrawFontBitmap16x24(result);
	}
	if (show_name2 == 1)
	{
		if (key == FSKEY_ENTER)
		{
			show_name2 = 0;
			gameplayer2.set_name(result1);
		}
		else if (key == FSKEY_BS)
		{
			if (counter2 > 0)
			{
				counter2--;
				result1[counter2] = 0;
			}
		}
		else if (key != FSKEY_NULL)
		{
			if (5 >= counter2 && '0' != checkkey(key))
			{
				result1[counter2] = checkkey(key);
				counter2++;
			}
		}
		glColor3f(255, 0, 0);
		glRasterPos2i(450, 345);
		YsGlDrawFontBitmap16x24(result1);
	}
}

void Menu::IntroState1(int mx, int my, int mouseEvent, int& terminate, int& state)
{
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2d(600, 180);
	glVertex2d(600, 380);
	glVertex2d(1300, 380);
	glVertex2d(1300, 180);
	glEnd();
	glColor3f(0, 0, 0);
	glRasterPos2i(700, 245);
	YsGlDrawFontBitmap32x48("Element Bounce");

	glColor3f(0, 0, 0);
	glRasterPos2i(700, 345);
	YsGlDrawFontBitmap20x32("Angry 2048 Team");

	if (mx > 190 && mx < 300 && my > 220 && my < 255)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 245);
		YsGlDrawFontBitmap20x32("Start");
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 245);
		YsGlDrawFontBitmap16x24("Start");
	}
	if (mx > 190 && mx < 420 && my > 320 && my < 355)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 345);
		YsGlDrawFontBitmap20x32("Instruction");
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 345);
		YsGlDrawFontBitmap16x24("Instruction");
	}
	if (mx > 190 && mx < 300 && my > 420 && my < 455)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 445);
		YsGlDrawFontBitmap20x32("Exit");
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 445);
		YsGlDrawFontBitmap16x24("Exit");
	}
	switch (mouseEvent)
	{
	case FSMOUSEEVENT_LBUTTONDOWN:
		break;
	case FSMOUSEEVENT_LBUTTONUP:
		if (mx > 190 && mx < 300 && my > 220 && my < 255)
		{
			state = 1;
		}
		if (mx > 190 && mx < 420 && my > 320 && my < 355)
		{
			state = 4;
		}
		if (mx > 190 && mx < 300 && my > 420 && my < 455)
		{
			terminate = 1;//exit the game
			state = 100;
		}
		break;
	}
}

void Menu::IntroState2(int mx, int my, int mouseEvent, int& state, int& gamemode, int& totalround, int key, player& gameplayer1, player& gameplayer2)
{
	//render
	if (show_name1 == 1)
	{
		glBegin(GL_QUADS);
		glColor3f(0, 255, 255);
		glVertex2i(450, 255);
		glVertex2i(450, 210);
		glVertex2i(600, 210);
		glVertex2i(600, 255);
		glEnd();
	}
	else if (show_name1 == 0)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(500, 245);
		YsGlDrawFontBitmap16x24(result);
	}
	if (show_name2 == 1)
	{
		glBegin(GL_QUADS);
		glColor3f(0, 255, 255);
		glVertex2i(450, 355);
		glVertex2i(450, 310);
		glVertex2i(600, 310);
		glVertex2i(600, 355);
		glEnd();
	}
	else if (show_name2 == 0)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(500, 345);
		YsGlDrawFontBitmap16x24(result1);
	}

	//mouse check
	if (mx > 190 && mx < 425 && my > 220 && my < 255)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 245);
		YsGlDrawFontBitmap20x32("Player1's name");
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 245);
		YsGlDrawFontBitmap16x24("Player1's name");
	}
	if (mx > 190 && mx < 425 && my > 320 && my < 355)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 345);
		YsGlDrawFontBitmap20x32("Player2's name");
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 345);
		YsGlDrawFontBitmap16x24("Player2's name");
	}
	if (mx > 190 && mx < 325 && my > 420 && my < 455)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 445);
		YsGlDrawFontBitmap20x32("Game Mode");
		glColor3ub(100, 100, 255);
		glBegin(GL_QUADS);
		glVertex2d(420, 405);
		glVertex2d(420, 455);
		glVertex2d(620, 455);
		glVertex2d(620, 405);
		glEnd();
		if (0 == gamemode)
		{
			glColor3f(255, 0, 0);
			glRasterPos2i(430, 445);
			YsGlDrawFontBitmap16x24("Quick Game");
			glColor3ub(100, 100, 255);
			glBegin(GL_QUADS);
			glVertex2d(630, 405);
			glVertex2d(630, 455);
			glVertex2d(690, 455);
			glVertex2d(690, 405);
			glEnd();
			if (0 == roundstate)
			{
				char roundnum1[256];
				sprintf(roundnum1, "%d", totalround);
				glColor3f(255, 0, 0);
				glRasterPos2i(635, 445);
				YsGlDrawFontBitmap16x24(roundnum1);
			}
			else
			{
				glColor3f(0, 0, 0);
				glRasterPos2i(635, 445);
				YsGlDrawFontBitmap16x24(roundnum2);
			}
		}
		else if (1 == gamemode)
		{
			glColor3f(255, 0, 0);
			glRasterPos2i(430, 445);
			YsGlDrawFontBitmap16x24("2048 Game");
		}
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 445);
		YsGlDrawFontBitmap16x24("Game Mode");
		glColor3ub(100, 100, 255);
		glBegin(GL_QUADS);
		glVertex2d(420, 405);
		glVertex2d(420, 455);
		glVertex2d(620, 455);
		glVertex2d(620, 405);
		glEnd();
		if (0 == gamemode)
		{
			glColor3f(255, 0, 0);
			glRasterPos2i(430, 445);
			YsGlDrawFontBitmap16x24("Quick Game");
			glColor3ub(100, 100, 255);
			glBegin(GL_QUADS);
			glVertex2d(630, 405);
			glVertex2d(630, 455);
			glVertex2d(690, 455);
			glVertex2d(690, 405);
			glEnd();
			if (0 == roundstate)
			{
				char roundnum1[256];
				sprintf(roundnum1, "%d", totalround);
				glColor3f(255, 0, 0);
				glRasterPos2i(635, 445);
				YsGlDrawFontBitmap16x24(roundnum1);
			}
			else
			{
				glColor3f(0, 0, 0);
				glRasterPos2i(635, 445);
				YsGlDrawFontBitmap16x24(roundnum2);
			}
		}
		else if (1 == gamemode)
		{
			glColor3f(255, 0, 0);
			glRasterPos2i(430, 445);
			YsGlDrawFontBitmap16x24("2048 Game");
		}
	}
	if (mx > 190 && mx < 325 && my > 520 && my < 555)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 545);
		YsGlDrawFontBitmap20x32("Continue");
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 545);
		YsGlDrawFontBitmap16x24("Continue");
	}
	if (mx > 190 && mx < 325 && my > 620 && my < 645)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 645);
		YsGlDrawFontBitmap20x32("Back");
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 645);
		YsGlDrawFontBitmap16x24("Back");
	}

	if (1 == roundstate)
	{
		if (key == FSKEY_ENTER)
		{
			roundstate = 0;
			totalround = atoi(roundnum2);
			printf("a");
		}
		else if (key == FSKEY_BS)
		{
			if (roundcounter > 0)
			{
				roundcounter--;
				roundnum2[roundcounter] = 0;
			}
		}
		else if (key == FSKEY_0 || key == FSKEY_1 || key == FSKEY_2 || key == FSKEY_3 || key == FSKEY_4 || key == FSKEY_5 || key == FSKEY_6 || key == FSKEY_7 || key == FSKEY_8 || key == FSKEY_9)
		{
			if (1 >= roundcounter)
			{
				roundnum2[roundcounter] = key + '0' - 2;
				roundcounter++;
			}
		}
	}

	//mouse event
	switch (mouseEvent)
	{
	case FSMOUSEEVENT_LBUTTONDOWN:
		if (mx > 190 && mx < 325 && my > 420 && my < 455)
		{
			if (0 == gamemode)
			{
				gamemode = 1;
			}
			else if (1 == gamemode)
			{
				gamemode = 0;
			}
		}
		if (mx > 630 && mx < 690 && my > 405 && my < 455)
		{
			roundstate = 1;
		}
	case FSMOUSEEVENT_LBUTTONUP:
		if (mx > 190 && mx < 450 && my > 220 && my < 255 && show_name2 != 1)
		{
			show_name1 = 1;
		}
		else if (mx > 190 && mx < 450 && my > 320 && my < 355 && show_name1 != 1)
		{
			show_name2 = 1;
		}
		else if (mx > 190 && mx < 325 && my > 520 && my < 555)
		{
			state = 2;
		}
		else if (mx > 190 && mx < 325 && my > 620 && my < 655)
		{
			state = 0;
		}
		break;
	}

	Type(key, gameplayer1, gameplayer2);
}

void Menu::GameEnd(player gameplayer1, player gameplayer2, int mx, int my, int mouseEvent, int& terminate, int& state)
{
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2d(300, 230);
	glVertex2d(1000, 230);
	glVertex2d(1000, 570);
	glVertex2d(300, 570);
	glEnd();
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(320, 250);
	glVertex2d(980, 250);
	glVertex2d(980, 550);
	glVertex2d(320, 550);
	glEnd();

	glColor3ub(255, 255, 255);
	glRasterPos2d(370, 380);
	YsGlDrawFontBitmap20x32("Game End");
	if (gameplayer1.get_score() > gameplayer2.get_score())
	{
		glColor3ub(255, 0, 0);
		glRasterPos2d(370, 450);
		YsGlDrawFontBitmap20x32("Player 1 Win, Congratulations!");
	}
	else if (gameplayer1.get_score() < gameplayer2.get_score())
	{
		glColor3ub(0, 0, 255);
		glRasterPos2d(370, 450);
		YsGlDrawFontBitmap20x32("Player 2 Win, Congratulations!");
	}
	else
	{
		glColor3ub(255, 255, 255);
		glRasterPos2d(370, 450);
		YsGlDrawFontBitmap20x32("Tie, Good Game!");
	}

	if (mx > 190 && mx < 300 && my > 620 && my < 655)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 645);
		YsGlDrawFontBitmap20x32("Back");
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(210, 645);
		YsGlDrawFontBitmap16x24("Back");
	}
	if (mx > 590 && mx < 800 && my > 620 && my < 655)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(610, 645);
		YsGlDrawFontBitmap20x32("Exit");
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(610, 645);
		YsGlDrawFontBitmap16x24("Exit");
	}
	switch (mouseEvent)
	{
	case FSMOUSEEVENT_LBUTTONDOWN:
		break;
	case FSMOUSEEVENT_LBUTTONUP:
		if (mx > 190 && mx < 300 && my > 620 && my < 655)
		{
			state = 1;
		}
		if (mx > 590 && mx < 800 && my > 620 && my < 655)
		{
			terminate = 1;//exit the game
			state = 100;
		}
		break;
	}
}

void Menu::Instruction(int mx, int my, int mouseEvent, int& terminate, int& state)
{

	if (mx > 1190 && mx < 1300 && my > 720 && my < 755)
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(1210, 745);
		YsGlDrawFontBitmap20x32("Back");
	}
	else
	{
		glColor3f(255, 0, 0);
		glRasterPos2i(1210, 745);
		YsGlDrawFontBitmap16x24("Back");
	}

	switch (mouseEvent)
	{
	case FSMOUSEEVENT_LBUTTONDOWN:
		break;
	case FSMOUSEEVENT_LBUTTONUP:
		if (mx > 1190 && mx < 1300 && my > 720 && my < 755)
		{
			state = 0;
		}
		break;
	}
}
