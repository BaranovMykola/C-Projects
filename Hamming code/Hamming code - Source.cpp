#include <iostream>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include "Hamming.h"

using namespace std;

template<typename T = Hamming>
bool test_decode()
{
	bool isCorrect = true;
	std::ifstream code("decimal_code.txt");
	std::ifstream answerd("decimal_code.txt");
	T test;
	char ans[5];
	while (!code.eof())
	{
		code >> test;
		answerd >> ans;
		char* _ch_bin = test.decode();
		if (*ans != *_ch_bin)
		{
			isCorrect = false;
			break;
		}
		delete[] _ch_bin;
	}
	return isCorrect;
}

template<typename T = Hamming>
bool test_repair()
{
	bool isCorrect = true;
	T test;
	std::ifstream code("code.txt");
	while (!code.eof())
	{
		code >> test;
		char* _ch_default;
		_ch_default = test.decode();
		for (int i = 0;i < 7;++i)
		{
			test.change_bit(i);
			test.repair();
			char* _ch_decode = test.decode();
			if (*_ch_decode != *_ch_default)
			{
				isCorrect = false;
				break;
			}
			delete[] _ch_decode;
		}
		delete[] _ch_default;
	}
	return isCorrect;
}

template<typename T = Hamming>
bool test_memory()
{
	_CrtMemState state1, state2, state3;
	_CrtMemCheckpoint(&state1);
	{
		test_repair<T>();
		test_decode<T>();
	}
	_CrtMemCheckpoint(&state2);
	return !_CrtMemDifference(&state3, &state1, &state2);

}

template<typename T = Hamming>
bool test_constructor()
{
	bool isCorrect = true;
	const unsigned short int _i_dec[4] = { 1,3,6,13 };
	const char _ch_bin[4][5] = { "0001", "0011", "0110", "1101" };
	for (int i = 0;i < 4;++i)
	{
		T test = _i_dec[i];
		char* _ch_decode = test.decode();
		if (*_ch_bin[i] != *_ch_decode)
		{
			isCorrect = false;
			break;
		}
		delete[] _ch_decode;
		test = _ch_bin[i];
		_ch_decode = test.decode();
		if (*_ch_bin[i] != *_ch_decode)
		{
			isCorrect = false;
			break;
		}
		delete[] _ch_decode;
	}
	return isCorrect;
}

void main()
{
	try
	{
		_CrtMemState state1, state2, state3;
		_CrtMemCheckpoint(&state1);
		{
			cout << "\t\tUnit test block:" << endl;
			cout << "\tHamming code(7,4):" << endl;
			cout << "Test repair:\t\t" << boolalpha << test_repair() << endl;
			cout << "Test decode & _btoi:\t" << boolalpha << test_decode() << endl;
			cout << "Test constructor:\t" << boolalpha << test_constructor() << endl;
			cout << "Test memory:\t\t" << boolalpha << test_memory() << endl;
			cout << "\tHamming code(8,4):" << endl;
			cout << "Test repair:\t\t" << boolalpha << test_repair<Hamming8>() << endl;
			cout << "Test decode & _btoi:\t" << boolalpha << test_decode<Hamming8>() << endl;
			cout << "Test constructor:\t" << boolalpha << test_constructor<Hamming8>() << endl;
			cout << "Test memory:\t\t" << boolalpha << test_memory<Hamming8>() << endl << setw(120) << setfill('*') << '*' << endl;

			Hamming8 a;
			char* decode;
			cout << "Type binary code (no more 4 bits): ";
			cin >> a;

			cout << "Hamming code (8,4)\t" << a << endl;
			decode = a.decode();
			cout << "Deocde:\t" << decode << endl;
			delete[] decode;

			unsigned short int error;
			bool quantity = false;
			cout << "\t\tInterference block:" << endl;
			cout << "Two error: ";
			cin >> quantity;
			for (int i = 0;i < 1 + quantity;++i)
			{
				cout << "Change bit: ";
				cin >> error;
				a.change_bit(error);
			}
			cout << "\t\tError block code:" << endl;
			short int error_bit = a.get_error();
			a.format_error(error_bit);
			cout << endl << "Error in code: " << error_bit << endl;
			cout << "Bad code:\t" << a << endl;
			decode = a.decode();
			cout << "Deocde:\t" << decode << endl; 
			delete[] decode;

			a.repair();

			cout << "\t\tRepairing..." << endl << endl;
			cout << "Hamming code (8,4)\t" << a << endl;
			decode = a.decode();
			cout << "Deocde:\t" << decode << endl;
			delete[] decode;
		}
		_CrtMemCheckpoint(&state2);
		if (_CrtMemDifference(&state3, &state1, &state2))
		{
			throw exception("Memory error");
		}
	}
	catch(exception error)
	{
		cout << endl << setw(120) << setfill('*') << '*' << endl << "\t\tException error: " << error.what() << endl << endl << setw(120) << '*' << endl;
	}
	system("pause");
}