#include <iostream>
#include <ctime>
#include <iomanip>
#include "TuringMachine.h"

using namespace std;

bool test_copy();

bool test_multiply();

time_t test_speed();

bool test_memory();

void main()
{
	try
	{
		_CrtMemState state1, state2, state3;
		_CrtMemCheckpoint(&state1);
		{
			cout << "\t\tUnit test block:" << endl;
			cout << "Copy test:\t\t" << boolalpha << test_copy() << endl;
			cout << "Mathematical test:\t" << boolalpha << test_multiply() << endl;
			cout << "Memory test:\t\t" << boolalpha << test_memory() << endl;
			cout << "Speed test 20x20:\t" << boolalpha << test_speed() << endl;
			cout << setw(120) << setfill('*') << '*' << endl;
			string in;
			map<_Key, _Value> rules;
			ifstream file("copy_rules.txt");
			while (!file.eof())
			{
				_Key first;
				_Value second;
				file >> first >> second;
				rules.insert(pair<_Key, _Value>(first, second));
			}
			TuringMachine demo(rules);
			cout << "\t\tCopy:" << endl;
			cout << "Input start configuration (binary code):\t";
			cin >> in;
			cout << "Begin:\t" << in << endl;
			demo.set_configuration(in);
			demo.run();
			cout << "End:\t" << demo.get_configuration() << endl;

			cout << setw(120) << setfill('*') << '*' << endl;

			file.close();
			file.open("multiply_rules.txt");
			rules.clear();
			while(!file.eof())
			{
				_Key first;
				_Value second;
				file >> first >> second;
				rules.insert(pair<_Key, _Value>(first, second));
			}
			demo.set_program(rules);
			cout << "\t\tMultiplication:" << endl;
			cout << "Input start configuration (unary system exploded by '|'):\t";
			cin >> in;
			cout << "Begin:\t" << in << endl;
			demo.set_configuration(in);
			demo.run();	
			cout << "End:\t" << demo.get_configuration() << endl;
		}
		_CrtMemCheckpoint(&state2);
		if (_CrtMemDifference(&state3, &state1, &state2))
		{
			throw std::exception("Error memory");
		}
	}
	catch(exception error)
	{
		cout << setw(120) << setfill('*') << '*' << endl << "Error: " << error.what() << endl << setw(120) << setfill('*') << '*' << endl;
	}
	system("pause");
}

bool test_copy()
{
	bool isCorrect = true;
	string in;
	string out;
	ifstream data("copy_data.txt");
	ifstream program("copy_rules.txt");
	map<_Key, _Value> target;
	while (!program.eof())
	{
		_Key from;
		_Value to;
		program >> from >> to;
		target.insert(pair<_Key, _Value>(from, to));
	}
	TuringMachine test(target);
	while (!data.eof())
	{
		data >> in >> out;
		test.set_configuration(in);
		test.run();
		isCorrect = (isCorrect && (test.get_configuration() == out));
	}
	return isCorrect;
}

bool test_multiply()
{
	bool isCorrect = true;
	string in;
	unsigned int out;
	ifstream data("multiply_data.txt");
	ifstream program("multiply_rules.txt");
	map<_Key, _Value> target;
	while (!program.eof())
	{
		_Key from;
		_Value to;
		program >> from >> to;
		target.insert(pair<_Key, _Value>(from, to));
	}
	TuringMachine test(target);
	while (!data.eof())
	{
		data >> in >> out;
		test.set_configuration(in);
		test.run();
		string str_result = test.get_configuration();
		unsigned int result = 0;
		for (char i : str_result)
		{
			if (i == '1')
			{
				++result;
			}
		}
		--result;
		isCorrect = (isCorrect && (result == out));
	}
	return isCorrect;
}

time_t test_speed()
{
	ifstream program("multiply_rules.txt");
	map<_Key, _Value> target;
	while (!program.eof())
	{
		_Key from;
		_Value to;
		program >> from >> to;
		target.insert(pair<_Key, _Value>(from, to));
	}
	TuringMachine test(target);
	test.set_configuration("111111111111111111111|111111111111111111111");
	time_t start = clock();
	test.run();
	return clock() - start;
}

bool test_memory()
{
	bool isCorrect = true;
	_CrtMemState state1, state2, state3;
	_CrtMemCheckpoint(&state1);
	{
		test_copy();
		test_multiply();
	}
	_CrtMemCheckpoint(&state2);
	if (_CrtMemDifference(&state3, &state1, &state2))
	{
		isCorrect = false;
	}
	return isCorrect;
}