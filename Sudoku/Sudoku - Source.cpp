#include <iostream>
#include <ctime>
#include "Sudoku.h"

using namespace std;

void main()
{
	time_t old = time(0);
	_CrtMemState state1, state2, state3;
	_CrtMemCheckpoint(&state1);
	{
		Sudoku a;
		a.fill();
		cout << a << endl;
	}
	_CrtMemCheckpoint(&state2);
	if (_CrtMemDifference(&state3, &state1, &state1))
	{
		cout << "Error memory..." << endl;
	}
	cout << "Time running: " << (time(0) - old) / 1000.0 << " s." << endl;
	system("pause");
}