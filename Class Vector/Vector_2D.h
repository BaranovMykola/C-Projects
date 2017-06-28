#pragma once
#include "Point.h"

class Vector
{
	int a;
	int b;
public:
	Vector(int=0, int=0);
	Vector(Point&, Point&);
	double norm();
	double angle(Vector&);
	~Vector_2D();
};

