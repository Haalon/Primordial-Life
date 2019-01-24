#ifndef __FIELD_H__
#define __FIELD_H__

#include "CImg.h"
#include "vector2.h"

const double PI = 3.14159265358979323846;

const unsigned char
    red[]   = { 255,0,0 },
    green[] = { 0,255,0 },
    blue [] = { 0,0,255 },
    white[] = {255, 255, 255},
    cyan[] = {0,255, 255},
    magenta[] = {255, 0 , 255},
    yellow[] = { 255, 255, 0},
    gray[] = {127, 127 , 127},
    dark_gray[] = {63, 63, 63},
    light_gray[] = {191, 191, 191};


struct Particle
{

	Vector2 pos;
	double ang;

	int N = 0;

	Particle(double x = 0, double y = 0, double a = 0) : pos(x,y), ang(a) {}
};

class Field
{

	int width;
	int height;

	Particle ** body;
	Particle ** body2;

	int count;

	double alpha = PI;
	double beta = PI/180*17;
	double vel = 0.67*10;
	double rad = 25;

	double draw_rad = 3;


public:

	long step = 0;
	cimg_library::CImg<unsigned char>* img;

	Field(int w, int h, int c);
	~Field();

	void preUpdateOne(int indx);
	void update();
	

	cimg_library::CImg<unsigned char>& show();
	
};

#endif

