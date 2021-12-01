#ifndef MENU_IS_INCLUDED
#define  MENU_IS_INCLUDED

#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "player.h"

class Menu
{
private:
	int show_name1 = 0, show_name2 = 0;//print name state
	int counter1 = 0, counter2 = 0;//length of player's name
	char result[256], result1[256];//player1's name and player 2's name

	int roundstate = 0, roundcounter = 2;//roundprint, round length
	char roundnum2[256];

	char checkkey(int key);//help function used to check the input key
	void Type(int key, player& gameplayer1, player& gameplayer2);//state == 1, typing
public:
	Menu();
	void IntroState1(int mx, int my, int mouseEvent, int& terminate, int& state);//state == 0, render

	void IntroState2(int mx, int my, int mouseEvent, int& state, int& gamemode, int& totalround, int key, player& gameplayer1, player& gameplayer2);//state == 1, render
	

	void GameEnd(player gameplayer1, player gameplayer2, int mx, int my, int mouseEvent, int& terminate, int& state);// state == 3, game end page

	void Instruction(int mx, int my, int mouseEvent, int& terminate, int& state);// state == 4
};

#endif