#pragma once
#include <cmath>

struct Point
{
	int x;
	int y;
	Point(int=0, int=0);
	friend double distnace(Point&, Point&);
	~Point();
};

