#ifndef BALL_IS_INCLUDED
#define BALL_IS_INCLUDED

#include "DrawBasket.h"

const double Pi = 3.1415927;

using namespace std;


class NumberBall
{
private:
    int numdic[11] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
    double rdic[11] = { 25, 25, 25, 25, 25, 25, 30, 30, 30, 40, 40 };
    int reddic[11] = { 128,255,255,135,128,51,0,138,0,220,255 };
    int bluedic[11] = { 128,222,0,38,42,161,201,43,199,220,215 };
    int greendic[11] = { 105,173,0,87,42,201,87,226,140,220,0 };
    int red = 0, green = 0, blue = 0;
public:
    double x = 0, y = 0, r = 0; // coordinates of center of ball
    double vx = 0, vy = 0; //ball velocities
    int State = 0, num = 2;

    void Initialize(double xpos, double ypos, int number);
    void accelerate(double dt);
    void Move(double dt);
    void SetPosition(double x0, double y0);
    void SetV0(double vx0, double vy0);
    void CheckHitBasket(double dt);
    void Stop();
    void Bounce_corner(double x1);
    void Bounce_ball(double x1);

    void Draw(void);
};

void Combine(NumberBall one, NumberBall two, NumberBall& newball);

bool CheckBallHit(NumberBall& one, NumberBall& two,double dt);

#endif