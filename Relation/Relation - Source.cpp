#include <iostream>
#include <iomanip>
#include "Relation.h"


using namespace std;
void main()
{
	try
	{
		_CrtMemState state1, state2, state3;
		_CrtMemCheckpoint(&state1);
		{
			cout << "\t\tUnit test block:" << endl;
			cout << setw(120) << setfill('*') << '*' << endl << endl;
			cout << setw(120) << setfill('*') << '*' << endl << endl;
		}
		_CrtMemCheckpoint(&state2);
		if (_CrtMemDifference(&state3, &state1, &state1))
		{
			throw exception("Error memory");
		}
	}
	catch (exception error)
	{
		cout << setw(120) << setfill('*') << '*' << endl << endl << error.what() << setw(120) << setfill('*') << '*' << endl << endl;
	}
	system("pause");
}