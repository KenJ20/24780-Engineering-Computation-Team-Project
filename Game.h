#ifndef GAME_IS_INCLUDED
#define GAME_IS_INCLUDED

#include <vector>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "ball.h"
#include "launcher.h"
#include "DrawBasket.h"
#include "player.h"

class Game
{
private:
	Launcher Player1;
	Launcher Player2;
	double cx1 = 40, cy1 = 300, csize1 = 4, cangle1 = Pi / 4, clow1 = 150, cup1 = 300, cvx1 = 0, cvy1 = 0;//Launcher1 setting
	double cx2 = 1260, cy2 = 300, csize2 = 4, cangle2 = 3 * Pi / 4, clow2 = 150, cup2 = 300, cvx2 = 0, cvy2 = 0;//Launcher2 setting
	int cstate1 = 0, cstate2 = 3;//State of launcher1 and launcher2

	int shootballnum = 2;//shooting ball num
	NumberBall shootball;//shooting ball
	std::vector <NumberBall> balls;//balls bag

	Basket show;//Beaker

	double dt = 0.03;//iteration interval
	double randbar = 0, randbar1 = 0, randbar2 = 0;//random choice ajustment
	double timecount = 0.0;//turn time counter
	long long int turntime = FsSubSecondTimer();//turn now time
	long long int turnstart = FsSubSecondTimer();//turn start time
	bool countstart = false;//turn state
	int roundnum = 0;//the number round

	void LaunchInTurn(YsSoundPlayer& player, YsSoundPlayer::SoundData& wav);
	void Shooting(int randnum);//state == 2, shooting
	int HitCombine(std::vector <NumberBall>& newballs);//state == 2, set velocity, check hit and combine
	void Moveballs();//state == 2, balls move
	void Drawballsbasket(player gameplayer1, player gameplayer2);//state == 2, draw ball and basket
	void ScoreChecker(player& gameplayer1, player& gameplayer2, int score);//state ==2, calculate score
	void BallStateChecker(std::vector <NumberBall>& newballs);//state == 2, pushback valid balls from balls to newballs
	void ShootBallTerminateChecker(std::vector <NumberBall>& newballs);// state == 2, shootball checker
	void RoundTerminateChecker(std::vector <NumberBall>& newballs, player& gameplayer1, player& gameplayer2);// state == 2, round end checker
	void GameTerminateChecker(int& state, int totalround, int gamemode);// state == 2, game end check
public:
	Game();
	void Reset(void);
	void GameOneIteration(YsSoundPlayer& soundplayer, YsSoundPlayer::SoundData& wav, player& gameplayer1, player& gameplayer2, int& state, int totalround, int gamemode, int randnum);

};



#endif