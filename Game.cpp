#include <vector>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "ball.h"
#include "launcher.h"
#include "DrawBasket.h"
#include "Game.h"
#include "player.h"

Game::Game()
{
	Player1.SetSizePosColour(cx1, cy1, csize1, Pi / 4, clow1, cup1, 0, 0, 0);
	Player2.SetSizePosColour(cx2, cy2, csize2, 3 * Pi / 4, clow2, cup2, 0, 0, 0);
	shootball.State = 0;
}

void Game::Reset(void)
{
	cx1 = 40, cy1 = 300, csize1 = 4, cangle1 = Pi / 4, clow1 = 150, cup1 = 300, cvx1 = 0, cvy1 = 0;//Launcher1 setting
	cx2 = 1260, cy2 = 300, csize2 = 4, cangle2 = 3 * Pi / 4, clow2 = 150, cup2 = 300, cvx2 = 0, cvy2 = 0;//Launcher2 setting
	cstate1 = 0, cstate2 = 3;//State of launcher1 and launcher2

	shootballnum = 2;//shooting ball num
	balls.clear();//balls bag

	dt = 0.03;//iteration interval
	randbar = 0, randbar1 = 0, randbar2 = 0;//random choice ajustment
	timecount = 0.0;//turn time counter
	turntime = FsSubSecondTimer();//turn now time
	turnstart = FsSubSecondTimer();//turn start time
	countstart = false;//turn state
	roundnum = 0;//the number round

	Player1.SetSizePosColour(cx1, cy1, csize1, Pi / 4, clow1, cup1, 0, 0, 0);
	Player2.SetSizePosColour(cx2, cy2, csize2, 3 * Pi / 4, clow2, cup2, 0, 0, 0);
	shootball.State = 0;
}

void Game::GameOneIteration(YsSoundPlayer& soundplayer, YsSoundPlayer::SoundData& wav, player& gameplayer1, player& gameplayer2, int& state, int totalround, int gamemode, int randnum)
{
	std::vector <NumberBall> newballs;
	int score = 0;
	LaunchInTurn(soundplayer, wav);
	Shooting(randnum);
	score = HitCombine(newballs);
	Moveballs();
	Drawballsbasket(gameplayer1, gameplayer2);
	ScoreChecker(gameplayer1, gameplayer2, score);
	BallStateChecker(newballs);
	ShootBallTerminateChecker(newballs);
	RoundTerminateChecker(newballs, gameplayer1, gameplayer2);
	GameTerminateChecker(state, totalround, gamemode);
}

void Game::LaunchInTurn(YsSoundPlayer& player, YsSoundPlayer::SoundData& wav)
{
	//cstate case
	//-1:choose the random shootball's number
	//0:wait for stockpiling
	//1:stockpiling
	//2:stockpiling stop and move according to LaunchiInTurn function
	//3:lock launcher
	//4:give initial velocity to the shootball
	//5:let ball move according to the rules in ball.cpp and wait for shootball terminate
	if (cstate1 != 2)
	{
		Player1.Rotate(FSKEY_A, FSKEY_D);
		Player1.UpDown(FSKEY_W, FSKEY_S, 200, 700);
	}
	if (cstate1 == 0 && cstate2 == 3)
	{
		if (true == Player1.Stockpile(FSKEY_SPACE, dt))
		{
			cstate1 = -1;
		}
	}
	else if (cstate1 == 1 && cstate2 == 3)
	{
		if (true == Player1.Stockpile(FSKEY_SPACE, dt))
		{
			cvx1 = Player1.v * cos(Player1.a);
			cvy1 = -Player1.v * sin(Player1.a);
			cx1 = Player1.x;
			cy1 = Player1.y - Player1.size * 19;
		}
		else
		{
			cstate1 = 2;
			player.PlayOneShot(wav);
		}
	}
	else if (cstate1 == -1 && cstate2 == 3)
	{
		if (true == Player1.Stockpile(FSKEY_SPACE, dt))
		{
			cstate1 = 1;
		}
	}

	if (cstate2 != 2)
	{
		Player2.Rotate(FSKEY_LEFT, FSKEY_RIGHT);
		Player2.UpDown(FSKEY_UP, FSKEY_DOWN, 200, 700);
	}
	if (cstate2 == 0 && cstate1 == 3)
	{
		if (true == Player2.Stockpile(FSKEY_ENTER, dt))
		{
			cstate2 = -1;
		}
	}
	else if (cstate2 == 1 && cstate1 == 3)
	{
		if (true == Player2.Stockpile(FSKEY_ENTER, dt))
		{
			cvx2 = Player2.v * cos(Player2.a);
			cvy2 = -Player2.v * sin(Player2.a);
			cx2 = Player2.x;
			cy2 = Player2.y - Player2.size * 19;
		}
		else
		{
			cstate2 = 2;
			player.PlayOneShot(wav);
		}
	}
	else if (cstate2 == -1 && cstate1 == 3)
	{
		if (true == Player2.Stockpile(FSKEY_ENTER, dt))
		{
			cstate2 = 1;
		}
	}


	if (cstate1 == 2 && cstate2 == 3)
	{
		cx1 += cvx1 * dt;
		cy1 += cvy1 * dt;
		if (cx1 >= Player1.x + Player1.size * cos(Player1.a) * Player1.len)
		{
			cstate1 = 4;
		}
	}
	if (cstate1 == 3 && cstate2 == 2)
	{
		cx2 += cvx2 * dt;
		cy2 += cvy2 * dt;
		if (cx2 <= Player2.x + Player2.size * cos(Player2.a) * Player2.len)
		{
			cstate2 = 4;
		}
	}

	if (cstate1 == 2 || cstate1 == 3 || cstate1 == 4 || cstate2 == 2 || cstate2 == 3 || cstate2 == 4)
	{
		if (YSTRUE == player.IsPlaying(wav))
		{
			player.KeepPlaying();
		}
	}
}

void Game::Shooting(int randnum)
{
	if (cstate1 == -1 || cstate2 == -1)
	{
		double randballseed = (double)randnum / (double)RAND_MAX;

		if (randballseed <= 0.25 - randbar)
		{
			shootballnum = 2;
		}
		else if (randballseed > 0.25 - randbar && randballseed <= 0.5 - 0.5 * randbar - randbar1)
		{
			shootballnum = 4;
		}
		else if (randballseed > 0.5 - 0.5 * randbar - randbar1 && randballseed <= 0.75 - 0.25 * randbar - 0.5 * randbar1 - randbar2)
		{
			shootballnum = 8;
		}
		else if (randballseed > 0.75 - 0.25 * randbar - 0.5 * randbar1 - randbar2 && randballseed <= 0.75 - 0.125 * randbar - 0.25 * randbar1 - 0.5 * randbar2)
		{
			shootballnum = 16;
		}
		else if (randballseed > 0.5 - 0.125 * randbar - 0.25 * randbar1 - 0.5 * randbar2 && randballseed <= 0.75 - 0.0625 * randbar - 0.125 * randbar1 - 0.25 * randbar2)
		{
			shootballnum = 32;
		}
		else if (randballseed > 0.75 - 0.0625 * randbar - 0.125 * randbar1 - 0.25 * randbar2)
		{
			shootballnum = 64;
		}
		shootball.Initialize(-100, -100, shootballnum);
	}

	if (cstate1 == 2 && cstate2 == 3)
	{
		shootball.SetPosition(cx1, cy1);
		shootball.State = 1;
	}
	else if (cstate1 == 3 && cstate2 == 2)
	{
		shootball.SetPosition(cx2, cy2);
		shootball.State = 1;
	}
	else if (cstate1 == 4 && cstate2 == 3)
	{
		shootball.SetV0(cvx1, cvy1);
		cstate1 = 5;
	}
	else if (cstate2 == 4 && cstate1 == 3)
	{
		shootball.SetV0(cvx2, cvy2);
		cstate2 = 5;
	}
}

int Game::HitCombine(std::vector <NumberBall>& newballs)
{
	int score = 0;

	for (auto& ball : balls)
	{
		ball.accelerate(dt);
	}
	if (cstate1 == 5 || cstate2 == 5)
	{
		shootball.accelerate(dt);
	}

	for (auto& ball : balls)
	{
		ball.CheckHitBasket(dt);
	}
	if (cstate1 == 5 || cstate2 == 5)
	{
		shootball.CheckHitBasket(dt);
	}


	for (int i = 0; i < balls.size(); ++i)
	{
		for (int j = i + 1; j < balls.size(); ++j)
		{

			if (true == CheckBallHit(balls[i], balls[j], dt))
			{
				NumberBall newball;
				Combine(balls[i], balls[j], newball);
				newballs.push_back(newball);
				score += (int)newball.num;
			}

		}
	}

	return score;
}

void Game::Moveballs()
{
	for (auto& ball : balls)
	{
		ball.Move(dt);

	}
	if (cstate1 == 5 || cstate2 == 5)
	{
		shootball.Move(dt);
	}
}

void Game::Drawballsbasket(player gameplayer1, player gameplayer2)
{
	for (auto& ball : balls)
	{
		ball.Draw();
	}
	if (shootball.State == 1)
	{
		shootball.Draw();
	}

	Player1.Draw(dt);
	Player2.Draw(dt);
	show.DrawBasket();
	show.DrawGround();

	char number[255];
	sprintf(number, "%d", shootball.num);
	glColor3f(0, 0, 0);
	if (1 == gameplayer1.state && 1 == cstate1)
	{
		glRasterPos2d(Player1.x - 10, Player1.y + 50);
		YsGlDrawFontBitmap16x20("Next:");
		glRasterPos2d(Player1.x + 70, Player1.y + 50);
		YsGlDrawFontBitmap16x20(number);
	}
	else if (1 == gameplayer2.state && 1 == cstate2)
	{
		glRasterPos2d(Player2.x - 70, Player2.y + 50);
		YsGlDrawFontBitmap16x20("Next:");
		glRasterPos2d(Player2.x + 10, Player2.y + 50);
		YsGlDrawFontBitmap16x20(number);
	}

	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(440, 700);
	glVertex2i(650, 700);
	glVertex2i(650, 800);
	glVertex2i(440, 800);
	glEnd();
	glColor3ub(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(650, 700);
	glVertex2i(860, 700);
	glVertex2i(860, 800);
	glVertex2i(650, 800);
	glEnd();
	char score1[255];
	sprintf(score1, "%d", gameplayer1.get_score());
	glColor3ub(255, 255, 255);
	glRasterPos2d(440, 720);
	YsGlDrawFontBitmap16x20("Player1:");
	if (nullptr != gameplayer1.get_name())
	{
		glColor3ub(255, 255, 255);
		glRasterPos2d(500, 750);
		YsGlDrawFontBitmap16x20(gameplayer1.get_name());
	}
	glColor3ub(255, 255, 255);
	glRasterPos2d(440, 770);
	YsGlDrawFontBitmap16x20("Score:");
	glColor3ub(255, 255, 255);
	glRasterPos2d(550, 770);
	YsGlDrawFontBitmap16x20(score1);

	char score2[255];
	sprintf(score2, "%d", gameplayer2.get_score());
	glColor3ub(255, 255, 255);
	glRasterPos2d(650, 720);
	YsGlDrawFontBitmap16x20("Player2:");
	if (nullptr != gameplayer2.get_name())
	{
		glColor3ub(255, 255, 255);
		glRasterPos2d(710, 750);
		YsGlDrawFontBitmap16x20(gameplayer2.get_name());
	}
	glColor3ub(255, 255, 255);
	glRasterPos2d(650, 770);
	YsGlDrawFontBitmap16x20("Score:");
	glColor3ub(255, 255, 255);
	glRasterPos2d(750, 770);
	YsGlDrawFontBitmap16x20(score2);

}

void Game::ScoreChecker(player& gameplayer1, player& gameplayer2, int score)
{
	//get score
	if (1 == gameplayer1.state)
	{
		gameplayer1.set_score(gameplayer1.get_score() + score);
	}
	else if (1 == gameplayer2.state)
	{
		gameplayer2.set_score(gameplayer2.get_score() + score);
	}
}

void Game::BallStateChecker(std::vector <NumberBall>& newballs)
{
	//ball state checker
	for (auto& ball : balls)
	{
		if (1 == ball.State)
		{
			newballs.push_back(ball);
		}
	}
}

void Game::ShootBallTerminateChecker(std::vector <NumberBall>& newballs)
{
	//shootball termination
	if (shootball.x - shootball.r >= 490 && shootball.x + shootball.r <= 810 && shootball.y + shootball.r <= 650 && shootball.y - shootball.r >= 230 && shootball.State == 1)
	{
		//start countdown
		turnstart = FsSubSecondTimer();
		countstart = true;

		//pushbask shootball
		newballs.push_back(shootball);
		shootball.State = 2;

		//change the launching possibility
		if (randbar < 0.25)
		{
			randbar += 0.025;
		}
		else
		{
			if (randbar1 < 0.26)
			{
				randbar1 += 0.026;
			}
			else
			{
				if (randbar2 < 0.26)
				{
					randbar2 += 0.026;
				}
			}
		}
	}
}

void Game::RoundTerminateChecker(std::vector <NumberBall>& newballs, player& gameplayer1, player& gameplayer2)
{
	//round time checker
	if (true == countstart)
	{
		turntime = FsSubSecondTimer() - turnstart;
		timecount = (double)turntime / 1000.0;
	}

	//round termination
	if (cstate1 == 5 || cstate2 == 5)
	{
		if ((timecount >= 5 && shootball.State == 2) || ((shootball.x - shootball.r >= 1300 || shootball.x + shootball.r <= 0 || shootball.y - shootball.r >= 800 || shootball.y + shootball.r <= 0) && shootball.State == 1))
		{
			//reset timer
			turnstart = turntime;
			countstart = false;
			timecount = 0.0;

			//round count
			roundnum += 1;
			//reset launcher
			cvx1 = 0, cvy1 = 0, cvx2 = 0, cvy2 = 0;
			shootball.State = 0;

			if (cstate1 == 5)
			{
				cstate1 = 3;
				cstate2 = 0;
				gameplayer1.state = 0;
				gameplayer2.state = 1;
			}
			if (cstate2 == 5)
			{
				cstate1 = 0;
				cstate2 = 3;
				gameplayer1.state = 1;
				gameplayer2.state = 0;
			}
		}
	}

	balls = newballs;
}

void Game::GameTerminateChecker(int& state, int totalround, int gamemode)
{
	if (totalround <= roundnum && 0 == gamemode)
	{
		state = 3;
	}

	if (1 == gamemode)
	{
		for (auto& ball : balls)
		{
			if (2048 == ball.num)
			{
				state = 3;
			}
		}
	}
}