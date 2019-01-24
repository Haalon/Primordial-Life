#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <math.h> 

struct Vector2
{
	double x;
	double y;
	Vector2(double xx = 0, double yy = 0) : x(xx), y(yy) {}

	double length()
	{
		return sqrt(x*x+y*y);
	}

	Vector2& rotate(double ang)
	{
		double nx = x*cos(ang)-y*sin(ang);
		double ny = x*sin(ang)+y*cos(ang);
		x = nx;
		y = ny;
		return (*this);

	}

	Vector2 norm()
	{
		return length() == 0 ? Vector2() : (*this)*(1/length());
	}

	Vector2& operator=(const Vector2& other)
	{
		x=other.x;
		y=other.y;
		return (*this);
	}

	Vector2& operator+=(const Vector2& other)
	{
		(*this) = (*this)+other;
		return (*this);
	}

	friend inline Vector2 operator+(const Vector2& left, const Vector2& right);
	friend inline Vector2 operator-(const Vector2& left, const Vector2& right);
	friend inline Vector2 operator*(double left, const Vector2& right);
	friend inline Vector2 operator*(const Vector2& left, double right);
	friend inline Vector2 operator*(const Vector2& left, const Vector2& right); // element-wise product
	friend inline double operator^(const Vector2& left, const Vector2& right); // dot product
};

double operator^(const Vector2& left, const Vector2& right)
{
	return left.x*right.x + left.y*right.y;
}

Vector2 operator+(const Vector2& left, const Vector2& right) 
{
    return Vector2(left.x + right.x, left.y + right.y);
}

Vector2 operator-(const Vector2& left, const Vector2& right) 
{
    return Vector2(left.x - right.x, left.y - right.y);
}

Vector2 operator*(double left, const Vector2& right) 
{
    return Vector2(left * right.x, left * right.y);
}

Vector2 operator*(const Vector2& left, double right) 
{
    return Vector2(left.x * right, left.y * right);
}

Vector2 operator*(const Vector2& left, const Vector2& right)
{
	return Vector2(left.x*right.x, left.y*right.y);
}

#endif