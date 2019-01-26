#include "field.h"
#include "CImg.h"
#include <random>
#include <math.h> 
#include "vector2.h"

using namespace cimg_library;
using namespace std;

Vector2 torus_dl(Vector2 v1, Vector2 v2, double w, double h) //shortest path on torus
{
	double nx,ny;
	double dx = v2.x-v1.x, dy = v2.y-v1.y;

	if( abs(dx) > w/2)
		nx = dx > 0 ? dx - w : w + dx;
	else
		nx = dx;

	if( abs(dy) > h/2)
		ny = dy > 0 ? dy - h : h + dy;
	else
		ny = dy;

	return Vector2(nx,ny);
}

Field::Field(int w, int h, int c, double a, double b) : width(w), height(h), count(c), alpha(a), beta(b)
{
	body = new Particle*[count];
	body2 = new Particle*[count];

	srand(time(0));
	img = new CImg<unsigned char>(w,h,1,3);

	for (int i = 0; i < count; ++i)
	{

		// body[i] = new Particle(width/2.0 + (double)rand()/RAND_MAX, height/2.0 +(double)rand()/RAND_MAX, (double)rand()/RAND_MAX *2 * PI);
		body[i] = new Particle((double)rand()/RAND_MAX * width, (double)rand()/RAND_MAX * height, (double)rand()/RAND_MAX *2 * PI );
		body2[i] = new Particle();			
	}
}
Field::~Field()
{
	for (int i = 0; i < count; ++i)
	{
		delete body[i];
		delete body2[i];
	}
	delete[] body;
	delete[] body2;
}

void Field::preUpdateOne(int indx)
{

	int l=0, r = 0;
	for (int i = 0; i < count; ++i)
	{
		if(i == indx)
			continue;
		// Vector2 dl = body[i]->pos - body[indx]->pos;
		Vector2 dl = torus_dl(body[indx]->pos,  body[i]->pos, width, height);
		if( dl.length() < rad)
		{
			dl = dl.rotate( -body[indx]->ang); //align it with particle
			if(dl.y > 0)
				l++;
			else
				r++;
		}		
	}

	Vector2 dl = Vector2(1,0).rotate(body[indx]->ang)*vel;
	double da = l > r ? beta * (r+l) : -beta * (r+l);
	// double da = l > r ? beta * l/(r+1) : -beta * r/(l+1);
	// double da = l > r ? beta * l : -beta * r;

	body2[indx]->pos = body[indx]->pos + dl;
	body2[indx]->ang = body[indx]->ang + da + alpha;
	body2[indx]->N = l + r;

	if(body2[indx]->pos.x < 0)
		body2[indx]->pos.x+=width;
	else if(body2[indx]->pos.x > width)
		body2[indx]->pos.x-=width;

	if(body2[indx]->pos.y < 0)
		body2[indx]->pos.y+=height;
	else if(body2[indx]->pos.y > height)
		body2[indx]->pos.y-=height;
}

void Field::update()
{
	
	#pragma omp parallel for 
	for (int i = 0; i < count; ++i)		
		preUpdateOne(i);
	

	auto temp = body;
	body = body2;
	body2 = temp;

	step++;

}

CImg<unsigned char>& Field::show()
{
	img->fill(0);
	const unsigned char * col;
	for (int i = 0; i < count; ++i)
	{
		col = dark_gray;
		if(body[i]->N > 30)
			col = white;
		else if(body[i]->N > 15)
			col = light_gray;
		else if(body[i]->N > 12)
			col = gray;
		img->draw_circle(body[i]->pos.x, body[i]->pos.y, draw_rad, col);
	}
	return (*img);
}
