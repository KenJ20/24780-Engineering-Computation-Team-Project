#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

void player::set_name(const char name1[])
{
	if (nullptr != name)
	{
		delete[] name;
		name = nullptr;
	}
	int len = strlen(name1);
	if (0 != len)
	{
		name = new char[len + 1];
		strcpy(name, name1);
	}
}

char* player::get_name(void) const
{
	return name;
}

int player::get_score(void) const
{
	return score;
}

void player::set_score(int newscore)
{
	score = newscore;
}