#pragma once
#include <fstream>

using namespace std;

template<typename _TyL = Literal, typename _TyR = Literal>
class Expretion
{
private:
	typedef _TyL value_type_left;
	typedef _TyR value_type_right;
	_TyL left;
	_TyR right;
public:
	Expretion();
};

