#ifndef PLAYER_IS_INCLUDED
#define PLAYER_IS_INCLUDED

class player
{
public:
	int state = 0, shootnum = 0;

	void set_name(const char name1[]);
	char* get_name(void) const;
	int get_score(void) const;
	void set_score(int point);
private:
	int score = 0;
	char* name = nullptr;
};

#endif

