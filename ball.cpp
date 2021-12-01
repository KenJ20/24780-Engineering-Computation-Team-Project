#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "ball.h"



void NumberBall::Initialize(double xpos, double ypos, int number)
{
    x = xpos;
    y = ypos;
    num = number;
    for (int i = 0; i < 11; i++)
    {
        if (num == numdic[i])
        {
            r = rdic[i];
            red = reddic[i];
            blue = bluedic[i];
            green = greendic[i];
        }
    }
    State = 1;
}

void NumberBall::accelerate(double dt)
{
    double fy = -70;//gravity
    double ay = -(fy / 1);
    double dx, dy;
    if (x - r >= 490 && x + r <= 810 && y - r >= 175 && y + r <= 650)
    {
        dx = 0.4;
        dy = 1;
    }
    else
    {
        dx = 0.08;
        dy = 0.08;
    }
    if (0 != vx)
    {
        vx = vx - (vx / abs(vx)) * dx * abs(vx) * dt;
    }
    if (0 != vy)
    {
        vy = vy - (vy / abs(vy)) * dy * abs(vy) * dt;
    }   
    vy += ay * dt;
}

void NumberBall::Move(double dt)
{
    x = x + vx * dt;
    y = y + vy * dt;
}

void NumberBall::SetPosition(double x0, double y0)
{
    x = x0;
    y = y0;
}

void NumberBall::SetV0(double vx0, double vy0)
{
    vx = vx0;
    vy = vy0;
}

void NumberBall::Stop() {
    vx = 0;
    vy = 0;
}

void NumberBall::CheckHitBasket(double dt)
{
    double rightb = x + r;
    double leftb = x - r;
    double upb = y - r;
    double lowb = y + r;
    if (vx > 0 && rightb > 440 && rightb < 490 && lowb < 700 && y > 175)//ball touches left outer edge of the basket
    {
        vx = -vx;
    }
    else if (vx < 0 && leftb > 810 && leftb < 860 && lowb < 700 && y > 175)//ball touches right outer edge of the basket
    {
        vx = -vx;
    }
    else if (vx < 0 && leftb > 440 && leftb < 490 && lowb < 700 && y > 175)//ball touches left inner edge of the basket
    {
        vx = -vx;
        x = 491 + r;
    }
    else if (vx > 0 && rightb < 860 && rightb > 810 && lowb < 700 && y > 175)//ball touches right inner edge of the basket
    {
        vx = -vx;
        x = 809 - r;
    }
    else if (y < 175 && lowb > 175 && pow((x - 490), 2) + pow((y - 175), 2) > pow(r, 2) && pow((x + vx * dt - 490), 2) + pow((y + vy * dt - 175), 2) < pow(r, 2))//ball touches left inner corner of the basket
    {
        Bounce_corner(490);
    }
    else if (y < 175 && lowb > 175 && pow((x - 810), 2) + pow((y - 175), 2) > pow(r, 2) && pow((x + vx * dt - 810), 2) + pow((y + vy * dt - 175), 2) < pow(r, 2))//ball touches right inner corner of the basket
    {
        Bounce_corner(810);
    }
    else if (x > 440 && x < 490 && lowb + vy * dt > 175 && lowb < 175)
    {
        vy = -vy;
    }
    else if (x > 810 && x < 860 && lowb + vy * dt > 175 && lowb < 175)
    {
        vy = -vy;
    }
    else if (lowb > 175 && upb < 225 && pow((x - 440), 2) + pow((y - 200), 2)>pow(r + 25, 2) && pow((x + vx * dt - 440), 2) + pow((y + vy * dt - 200), 2) < pow(r + 25, 2))//left outer corner touch
    {
        Bounce_ball(440);
    }
    else if (lowb > 175 && upb < 225 && pow((x - 860), 2) + pow((y - 200), 2)>pow(r + 25, 2) && pow((x + vx * dt - 860), 2) + pow((y + vy * dt - 200), 2) < pow(r + 25, 2))//left outer corner touch
    {
        Bounce_ball(860);
    }
    else if (lowb + vy * dt > 700 && lowb < 700)//ball touches ground
    {
        vy = -vy;
        vx = vx;
        if (rightb < 440)
        {
            vx = -150;
        }
        else if (leftb > 860)
        {
            vx = 150;
        }
    }
    else if (leftb > 440 && rightb < 860 && lowb + vy * dt > 650)//ball touches basket ground
    {
        double d = 650 - lowb;
        y = 649 - r;
        double run_time = ((-vy + sqrt(vy * vy + 2.0 * 98.0 * d)) / 98);
        if (d > 0)
        {
            vy = -vy + 98 * run_time;
        }
        else
        {
            vy = 0;
        }
        vx = vx;
    }

}

void NumberBall::Bounce_corner(double x1)
{
    if (vx < 0)
    {
        double v = sqrt(pow(vx, 2) + pow(vy, 2));//new speed combination
        double y_d = 230 - y;
        double x_d = x - x1;
        double angle = atan(y_d / x_d);
        vx = v * cos(angle);
        vy = -v * sin(angle);
        return;
    }
    else
    {
        double v = sqrt(pow(vx, 2) + pow(vy, 2));//new speed combination
        double y_d = 230 - y;
        double x_d = x - x1;
        double angle = atan(y_d / x_d);
        vx = v * cos(angle);
        vy = v * sin(angle);
        return;
    }
}

void NumberBall::Bounce_ball(double x1)
{
    if (vx > 0)
    {
        double v = sqrt(pow(vx, 2) + pow(vy, 2));//new speed combination
        double y_d = 200 - y;
        double x_d = x - x1;
        double angle = atan(y_d / x_d);
        vx = -v * cos(angle);
        vy = v * sin(angle);
        return;
    }
    else
    {
        double v = sqrt(pow(vx, 2) + pow(vy, 2));//new speed combination
        double y_d = 200 - y;
        double x_d = x - x1;
        double angle = atan(y_d / x_d);
        vx = v * cos(angle);
        vy = -v * sin(angle);
        return;
    }
}

void NumberBall::Draw()
{
    glColor3ub(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 64; ++i)
    {
        double a = (double)i * Pi / 32.0;
        double c = cos(a);
        double s = sin(a);
        glVertex2d(x + c * r, y + s * r);
    }
    glEnd();

    char number[255];
    sprintf(number, "%d", num);
    glColor3f(0, 0, 0);
    glRasterPos2d(x - 7, y + 5);
    YsGlDrawFontBitmap10x14(number);
}


void Combine(NumberBall one, NumberBall two, NumberBall& newball)
{
    double x1 = one.x;
    double y1 = one.y;
    double r1 = one.r;

    double x2 = two.x;
    double y2 = two.y;
    double r2 = two.r;

    double x_new = (x1 + x2) / 2;
    double y_new = (y1 + y2) / 2;

    double vx, vy;

    int new_num = one.num + two.num;

    newball.Initialize(x_new, y_new, new_num);
    if (one.vx >= two.vx)
    {
        vx = one.vx;
    }
    else
    {
        vx = two.vx;
    }
    if (one.vy >= two.vy)
    {
        vy = one.vy;
    }
    else
    {
        vy = two.vy;
    }
    newball.SetV0(vx, vy);
}


bool CheckBallHit(NumberBall& one, NumberBall& two,double dt)
{

    double x1 = one.x;
    double y1 = one.y;
    double r1 = one.r;

    double x2 = two.x;
    double y2 = two.y;
    double r2 = two.r;

    double dx = x2 - x1;
    double dy = y2 - y1;
    double dis = sqrt(dx * dx + dy * dy);
    if (dis <= (r1 + r2))
    {
        if (one.num == two.num)
        {
            one.Stop();
            two.Stop();
            one.State = 0;
            two.State = 0;
            return true;
        }
        else
        {
            double rvx = two.vx - one.vx;
            double rvy = two.vy - one.vy;
            if (dx * rvx + dy * rvy < 0.0)
            {
                if (dis < 1.0e-6)
                {
                    return false;
                }
                dx /= dis;
                dy /= dis;

                double k1 = one.vx * dx + one.vy * dy;
                double k2 = two.vx * dx + two.vy * dy;

                one.vx = one.vx + dx * (k2 - k1);
                one.vy = one.vy + dy * (k2 - k1);
                two.vx = two.vx + dx * (k1 - k2);
                two.vy = two.vy + dy * (k1 - k2);
                
            }
        }
    }
    return false;
}

