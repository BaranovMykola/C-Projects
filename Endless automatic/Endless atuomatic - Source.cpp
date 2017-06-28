#include <iostream>
#include <string>
#include <ctime>
#include "Automatic.h"

using namespace std;

bool test_run();

time_t test_speed();

bool test_memory();

const bool manual_test = true;

bool test_run_out();

time_t test_speed_out();

bool test_memory_out();

void main()
{
	try
	{
		_CrtMemState state1, state2, state3;
		_CrtMemCheckpoint(&state1);
		{
			cout << "\t\t\tUnit test block:" << endl;
			cout << "Test twones: \t" << boolalpha << test_run() << endl;
			cout << "Test Memory: \t" << boolalpha << test_memory() << endl;
			cout << "Test speed twoness (10.000 lenght for twones 1^0): " << test_speed() << endl;
			cout << "Test reverse: \t" << boolalpha << test_run_out() << endl;
			cout << "Test speed reverse (10.000 lenght for twones 1^0): " << test_speed() << endl;
			cout << "Test Memory (OutAutomatic): \t" << test_memory_out() << endl;
			cout << setw(120) << setfill('*') << '*' << endl << endl;
			Automatic test(9, 2);
			ifstream twones("Twones.txt");
			twones >> test;
			cout << "\tTWONES AUTOMATIC" << endl << endl;
			cout << test << endl;
			string word;
			if (manual_test)
			{
				for (int i = 0;i < 4;++i)
				{
					cout << "Input binary word: ";
					cin >> word;
					cout << "\t\tCorrect: " << test.run(word.c_str()) << endl;
				}
				cout << setw(120) << setfill('*') << '*' << endl;
				OutAutomatic reverse;
				ifstream reverse_programm("Reverse.txt");
				cout << "\tREVERSE AUTOMATIC" << endl << endl;
				reverse_programm >> reverse;
				cout << reverse << endl;
				char* in = new char[1000];
				cout << "Reverse: Type binary word: ";
				cin >> in;
				cout << "\tReverse: " <<reverse.run(in) << endl;
				OutAutomatic deley(3);
				cout << setw(120) << setfill('*') << '*' << endl;
				ifstream deley_prgramm("Binary_deley.txt");
				deley_prgramm >> deley;
				cout << "\tDELEY AUTOMATIC" << endl << endl;
				cout << deley << endl;
				cout << "Deley: Type binary word: ";
				cin >> in;
				cout << "\tDeley: " << deley.run(in) << endl;
				delete[] in;
				cout << setw(120) << setfill('*') << '*' << endl;
			}
		}
		_CrtMemCheckpoint(&state2);
		if (_CrtMemDifference(&state3, &state1, &state2))
		{
			throw exception("Error memory");
		}
	}
	catch(exception error)
	{
		cout << endl << setw(120) << setfill('*') << '*' << endl << endl << "Error: " << error.what() << endl  << endl << setw(120) << setfill('*') << '*' << endl << endl;
	}
	system("pause");
}

bool test_run()
{
	string automatic_data[2] = { "Twones.txt", "Order.txt" };
	string _testing_data[4] = { "_true_twones_data.txt", "_false_twones_data.txt", "_true_order_data.txt", "_false_order_data.txt" };
	unsigned int _testing_data_file = 0;
	bool isCorrect = true;
	for (int i = 0;i < 2;++i)
	{
		Automatic test(9-4*i, 2+2*i);
		ifstream states(automatic_data[i]);
		states >> test;
		for (int j = 0;j < 2;++j)
		{
			ifstream in(_testing_data[_testing_data_file++]);
			size_t _size;
			in >> _size;
			string word;
			for (int i = 0;i < _size;++i)
			{
				in >> word;
				isCorrect = (isCorrect &&
								test.run(word.c_str()));
				if (j % 2 != 0)
				{
					isCorrect = !isCorrect;
				}
			}
		}
	}
	return isCorrect;
}

time_t test_speed()
{
	Automatic test(9, 2);
	ifstream twones("Twones.txt");
	twones >> test;
	const size_t _size = 10000;
	char* _ch = new char[_size+1];
	const char symbol[2] = { '0', '1' };
	for (int i = 0;i < _size;++i)
	{
		_ch[i] = symbol[rand() % 2];
	}
	_ch[_size] = '\0';
	time_t start = clock();
	test.run(_ch);
	time_t end = clock();
	delete[] _ch;
	return end - start;
}

bool test_memory()
{
	bool isCorrect = true;
	_CrtMemState state1, state2, state3;
	_CrtMemCheckpoint(&state1);
	{
		test_speed();
		test_run();
	}
	_CrtMemCheckpoint(&state2);
	if (_CrtMemDifference(&state3, &state1, &state2))
	{
		isCorrect = false;
	}
	return isCorrect;
}

bool test_run_out()
{
	bool isCorrect = true;
	const string _path_programm[2] = { "Reverse.txt", "Binary_deley.txt" };
	const string _path_data[2] = { "_reverse_data.txt", "_deley_data.txt" };
	for (int i = 0;i < 2;++i)
	{
		OutAutomatic test(1+i*2, 2);// (1,2) | (3,2)
		ifstream programm(_path_programm[i]);
		ifstream data(_path_data[i]);
		size_t lenght;
		data >> lenght;
		programm >> test;
		char* in = new char[lenght];
		char* out = new char[lenght];
		while (!data.eof())
		{
			data >> in >> out;
			isCorrect = (isCorrect && (*test.run(in) == *out));
		}
		delete[] in;
		delete[] out;
	}
	return isCorrect;
}

time_t test_speed_out()
{
	OutAutomatic test;
	ifstream programm("Reverse.txt");
	programm >> test;
	const size_t _size = 10000;
	char* _ch = new char[_size + 1];
	const char symbol[2] = { '0', '1' };
	for (int i = 0;i < _size;++i)
	{
		_ch[i] = symbol[rand() % 2];
	}
	_ch[_size] = '\0';
	time_t start = clock();
	test.run(_ch);
	time_t end = clock();
	delete[] _ch;
	return end - start;
}

bool test_memory_out()
{
	bool isCorrect = true;
	_CrtMemState state1, state2, state3;
	_CrtMemCheckpoint(&state1);
	{
		test_run_out();
		test_speed_out();
	}
	_CrtMemCheckpoint(&state2);
	if (_CrtMemDifference(&state3, &state2, &state1))
	{
		isCorrect = false;
	}
	return isCorrect;
}