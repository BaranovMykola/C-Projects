#include "Point.h"



Point::Point(int _x, int _y):
	x(_x),
	y(_y)
{
}


Point::~Point()
{
}

double distnace(Point &a, Point &b)
{
	return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
}
