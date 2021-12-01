#include "fssimplewindow.h"
#include "yssimplesound.h"
#include <math.h>
#include <stdio.h>
#include "launcher.h"

const double Pi = 3.1415927;

void Launcher::SetSizePosColour(double x1, double y1, double size1, double a1, double vLow1, double vUp1, int red1, int green1, int blue1)
{
	x = x1;
	y = y1;
	size = size1;
	a = a1;
	vLow = vLow1;
	v = vLow1;
	vUp = vUp1;
	red = red1;
	green = green1;
	blue = blue1;
	y += size * 19;
	if (a >= Pi / 2)
	{
		range = 1;
	}
	else
	{
		range = -1;
	}
}

void Launcher::Rotate(int keycounterwise, int keycounter)
{
	auto keystatecounterwise = FsGetKeyState(keycounterwise);
	auto keystatecounter = FsGetKeyState(keycounter);
	
	if (range == -1)
	{
		if (-Pi / 9 <= a && Pi / 2 >= a)
		{
			if (1 == keystatecounter)
			{
				a -= 0.05;
			}
			if (1 == keystatecounterwise)
			{
				a += 0.05;
			}
		}
		else if (-Pi / 9 >= a)
		{
			if (1 == keystatecounterwise)
			{
				a += 0.05;
			}
		}
		else if (Pi / 2 <= a)
		{
			if (1 == keystatecounter)
			{
				a -= 0.05;
			}
		}
	}
	else
	{
		if (Pi * 10 / 9 >= a && Pi / 2 <= a)
		{
			if (1 == keystatecounter)
			{
				a -= 0.05;
			}
			if (1 == keystatecounterwise)
			{
				a += 0.05;
			}
		}
		else if (10 * Pi / 9 <= a)
		{
			if (1 == keystatecounter)
			{
				a -= 0.05;
			}
		}
		else if (Pi / 2 >= a)
		{
			if (1 == keystatecounterwise)
			{
				a += 0.05;
			}
		}
	}
}

void Launcher::UpDown(int keyup, int keydown, double up, double down)
{
	auto keystateup = FsGetKeyState(keyup);
	auto keystatedown = FsGetKeyState(keydown);

	if (1 == keystateup && y >= up)
	{
		y -= 10;
	}
	if (1 == keystatedown && y <= down)
	{
		y += 10;
	}
}

bool Launcher::Stockpile(int keyhold, double dt)
{
	//input: dt(time interval)
	//return: True = during stockpile; False = else case
	//when false, the launch speed is always zero
	auto keystate = FsGetKeyState(keyhold);
	if (1 == keystate)
	{
		v += state * (vUp - vLow) * dt;
		if (v + state * (vUp - vLow) * dt >= vUp || v + state * (vUp - vLow) * dt <= vLow)
		{
			state = -state;
		}

		double x1 = x - (double)range * 50;
		glColor3ub(red, green, blue);
		glBegin(GL_LINES);
		glVertex2d(x1 - size * 20, y + 20);
		glVertex2d(x1 + size * 20, y + 20);
		glEnd();
		glColor3ub(red, green, blue);
		glBegin(GL_LINES);
		glVertex2d(x1 + size * 20, y + 30);
		glVertex2d(x1 - size * 20, y + 30);
		glEnd();
		glColor3ub(red, green, blue);
		glBegin(GL_LINES);
		glVertex2d(x1 + size * 20, y + 20);
		glVertex2d(x1 + size * 20, y + 30);
		glEnd();
		glColor3ub(red, green, blue);
		glBegin(GL_LINES);
		glVertex2d(x1 - size * 20, y + 20);
		glVertex2d(x1 - size * 20, y + 30);
		glEnd();
		glColor3ub(red, green, blue);
		glBegin(GL_QUADS);
		glVertex2d(x1 - size * 20, y + 20);
		glVertex2d(x1 - size * 20 + (v - vLow) / (vUp - vLow) * size * 40, y + 20);
		glVertex2d(x1 - size * 20 + (v - vLow) / (vUp - vLow) * size * 40, y + 30);
		glVertex2d(x1 - size * 20, y + 30);
		glEnd();

		tstate = true;
		return true;
	}
	state = 1;
	v = vLow;//reset velocity
	tstate = false;
	return false;
}

void Launcher::Draw(double dt)
{

	glColor3ub(red, green, blue);
	glBegin(GL_QUADS);
	glVertex2d(x - size * 15, y);
	glVertex2d(x + size * 15, y);
	glVertex2d(x + size * 15, y - size * 5);
	glVertex2d(x - size * 15, y - size * 5);
	glEnd();

	glColor3ub(red, green, blue);
	glBegin(GL_QUADS);
	glVertex2d(x - size * 3, y - size * 12);
	glVertex2d(x + size * 3, y - size * 12);
	glVertex2d(x + size * 3, y - size * 5);
	glVertex2d(x - size * 3, y - size * 5);
	glEnd();

	glColor3ub(red, green, blue);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 64; i++)
	{
		double a = (double)i * Pi / 32.0;
		double c = cos(a);
		double s = sin(a);

		glVertex2d(x + c * 10 * size, y - size * 19 + s * 10 * size);
	}
	glEnd();

	if (true == tstate)
	{
		if (10 > width)
		{
			width += 4 * dt;
		}
		if (16 < len)
		{
			len -= 4 * dt;
		}
		
	}
	if (false == tstate)
	{
		if (6 < width)
		{
			width -= 16 * dt;
		}
		if (20 > len)
		{
			len += 16 * dt;
		}
		
	}

	double x1 = x + size * len * cos(a) + size * width * sin(a);
	double y1 = y - size * 19 - size * len * sin(a) + size * width * cos(a);
	double x2 = x + size * 10 * sin(a);
	double y2 = y - size * 19  + size * 10 * cos(a);
	double x3 = x - size * 10 * sin(a);
	double y3 = y - size * 19  - size * 10 * cos(a);
	double x4 = x + size * len * cos(a) - size * width * sin(a);
	double y4 = y - size * 19 - size * len * sin(a) - size * width * cos(a);
	glColor3ub(red, green, blue);
	glBegin(GL_POLYGON);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glVertex2d(x3, y3);
	glVertex2d(x4, y4);
	glEnd();
}

