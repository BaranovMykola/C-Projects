#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <stack>

using std::ostream;
using std::vector;

const unsigned short int size = 9;

class Sudoku
{
	unsigned short int** field;
public:
	Sudoku();
	~Sudoku();
	void fill();
	bool check_row(unsigned short int);
	bool check_colum(unsigned short int);
	bool check_square(unsigned short int, unsigned short int);
	void set(unsigned short int, unsigned short int, unsigned short int);
	int* get_option();
	friend ostream& operator<<(ostream&, const Sudoku&);
};

