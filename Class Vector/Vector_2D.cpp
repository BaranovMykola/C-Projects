#include "Vector_2D.h"



Vector_2D::Vector_2D(int _a, int _b):
	a(_a),
	b(_b)
{
}

Vector_2D::Vector_2D(Point& _a, Point& _b):
	a(_b.x-_a.x),
	b(_b.y-_a.y)
{
}

double Vector_2D::norm()
{
	return sqrt(pow(a, 2) + pow(b, 2));
}

double Vector_2D::angle(Vector_2D &)
{
	return 0.0;
}


Vector_2D::~Vector_2D()
{
}
