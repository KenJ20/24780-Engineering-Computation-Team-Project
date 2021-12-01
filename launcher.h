#ifndef LAUNCHER_H_IS_INCLUDED
#define LAUNCHER_H_IS_INCLUDED

class Launcher
{
private:
	double width = 6;//len(tube length), width(tube width)
	double vLow = 0, vUp = 0;//threshold of velocity
	int red = 0, green = 0, blue = 0, range = 0;//colour(3ub)
	double state = 1;//stockpile state
	bool tstate = false;//tube change state 
public:
	double size = 0, v = 0, a = 0, x = 0, y = 0, len = 20; //x, y(center of the bottom line); size(launcher's size); 

	void SetSizePosColour(double x1, double y1, double size1, double a1, double vLow, double vUp, int red1, int green1, int blue1);//initialize from outside
	void Rotate(int keycounter, int keycounterwise);//rotate the tube
	void UpDown(int keyup, int keydown, double up, double down);//move the tube
	bool Stockpile(int keyhold, double dt);//stockpile, set speed
	void Draw(double dt);//draw launcher
};
#endif // ! LAUNCHER_H_IS_INCLUDED

