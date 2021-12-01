// team_project.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <stdlib.h>
#include <vector>
#include <time.h>
#include <stdio.h>
#include "player.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "Game.h"
#include "Menu.h"


bool LoadPng(YsRawPngDecoder& png, YsRawPngDecoder& png1, YsRawPngDecoder& png_inst)
{
	if (YSOK == png.Decode("background1.png"))
	{
		printf("Read Width=%d Height=%d\n", png.wid, png.hei);
		png.Flip();
	}
	else
	{
		printf("Read Error!\n");
		return false;
	}

	if (YSOK == png1.Decode("background2.png"))
	{
		printf("Read Width=%d Height=%d\n", png1.wid, png1.hei);
		png1.Flip();
	}
	else
	{
		printf("Read Error!\n");
		return false;
	}
    
    if (YSOK == png_inst.Decode("instruction.png"))
    {
        printf("Read Width=%d Height=%d\n", png1.wid, png1.hei);
        png_inst.Flip();
    }
    else
    {
        printf("Read Error!\n");
        return false;
    }

	return true;
}

int main()
{
    //FsChangeToProgramDir();
	//Random Number Seed
	//////////////////////////////////////////////////////////////
	srand(time(nullptr));
	///////////////////////////////////////////////////////////////

	//opengl initialize
	////////////////////////////////////////////////////////////
	FsOpenWindow(16, 16, 1300, 800, 1);
	int state = 0;
	int terminate = 0;//important state and exit number
	//////////////////////////////////////////////////////////

	//image initialization
	/////////////////////////////////////////////////////////
	YsRawPngDecoder png;
	YsRawPngDecoder png1;
    YsRawPngDecoder png_inst;
	if (false == LoadPng(png, png1, png_inst))
	{
		return 0;
	}
	////////////////////////////////////////////////////////////

	//sound initialization
	////////////////////////////////////////////////////////////////
	YsSoundPlayer SoundPlayer;
	SoundPlayer.Start();

	YsSoundPlayer::SoundData BackWav;
	BackWav.LoadWav("Background.wav");
	SoundPlayer.PlayBackground(BackWav);

	YsSoundPlayer::SoundData CannonWav;
	CannonWav.LoadWav("cannon.wav");
	//////////////////////////////////////////////////////////////

	//Player
	///////////////////////////////////////////////////////
	player gameplayer1;
	player gameplayer2;
	gameplayer1.state = 1;
	gameplayer2.state = 0;

	//Game Setting
	////////////////////////////////////////////////////////
	Menu gamemenu;
	Game game;
	int gamemode = 0;
	int totalround = 30;
	////////////////////////////////////////////////////////

	//Mouse Event
	////////////////////////////////////////////////////////
	int mouseEvent;
	int lb, mb, rb, mx, my;
	////////////////////////////////////////////////////////


	while (terminate == 0)//big while loop which maintain the game
	{
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		auto key = FsInkey();
		if (FSKEY_ESC == key)
		{
			break;
		}
		if (state == 0)//state 0 is the initial state which contains the initial background
		{
			//Draw background1
			///////////////////////////////////////////////////////////////////
			glRasterPos2i(0, 799);
			glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
			//////////////////////////////////////////////////////////////////

			//Mouse event & render
			/////////////////////////////////////////////////////////////////
			mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
			/////////////////////////////////////////////////////////////////

			gamemenu.IntroState1(mx, my, mouseEvent, terminate, state);
		}
		else if (state == 1)//State 1 is the start page
		{
			//Draw background1
			///////////////////////////////////////////////////////////////////
			glRasterPos2i(0, 799);
			glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
			///////////////////////////////////////////////////////////////////

			//Mouse event & render
			/////////////////////////////////////////////////////////////////////
			mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
			///////////////////////////////////////////////////////////////////

			gamemenu.IntroState2(mx, my, mouseEvent, state, gamemode, totalround, key, gameplayer1, gameplayer2);
			game.Reset();
			gameplayer1.set_score(0);
			gameplayer2.set_score(0);
		}
		else if (state == 2)//State 2 is the game setting page
		{
			//Draw background1
			///////////////////////////////////////////////////////////////////
			glRasterPos2i(0, 799);
			glDrawPixels(png1.wid, png1.hei, GL_RGBA, GL_UNSIGNED_BYTE, png1.rgba);
			///////////////////////////////////////////////////////////////////

			//Get random number
			///////////////////////////////////////////////////////////////////
			int randnum = rand();
			///////////////////////////////////////////////////////////////////

			game.GameOneIteration(SoundPlayer, CannonWav, gameplayer1, gameplayer2, state, totalround, gamemode, randnum);
		}
		else if (state == 3)//State 3 is the game
		{
			//Draw background1
			///////////////////////////////////////////////////////////////////
			glRasterPos2i(0, 799);
			glDrawPixels(png1.wid, png1.hei, GL_RGBA, GL_UNSIGNED_BYTE, png1.rgba);
			///////////////////////////////////////////////////////////////////

			mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
			gamemenu.GameEnd(gameplayer1, gameplayer2, mx, my, mouseEvent, terminate, state);
		}
		else if (state == 4)//State 4 is the instruction
		{
			//Draw background1
			///////////////////////////////////////////////////////////////////
			glRasterPos2i(0, 799);
			glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
			//////////////////////////////////////////////////////////////////
            
            //Draw instruction page
            ///////////////////////////////////////////////////////////////////
            glRasterPos2i(150, 660);
            glDrawPixels(png_inst.wid, png_inst.hei, GL_RGBA, GL_UNSIGNED_BYTE, png_inst.rgba);
            ///////////////////////////////////////////////////////////////////

			mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
			gamemenu.Instruction(mx, my, mouseEvent, terminate, state);
		}
		FsSwapBuffers();
		FsSleep(10);
	}
	SoundPlayer.End();

	return 0;
}


