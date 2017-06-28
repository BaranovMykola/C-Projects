#pragma once
#include <fstream>
#include <vector>
#include <iomanip>

using std::ostream;
using std::istream;

const int matrix[7] = { 1,2,3,4,5,6,7 };
const int dataOrder[4] = { 3,5,6,7 };
const int checkOrder[4] = { 1,2,4,8 };
const int extendedMatrix[8] = { 9,10,11,12,13,14,15,8 };

class Hamming
{
protected:
	unsigned short int code;//no much than 64
public:
	Hamming(const unsigned short int = 0);
	Hamming(const char*);
	~Hamming();
	friend ostream& operator<<(ostream&, const Hamming&);
	friend istream & operator>>(istream&, Hamming&);
	friend unsigned int _btoi(const char*);
	const bool* get_p(const int)const;
	void get_code(const bool*, int);
	void set_code(const unsigned short int);
	char* decode()const;
	void repair();
	unsigned short int get_error()const;
	void change_bit(unsigned short int, const unsigned short int = 6);// _k - max index of code. Index of lastest bit;
	void format_error(short int&)const;
};

class Hamming8 : public Hamming
{
public:
	Hamming8(const unsigned short int = 0);
	Hamming8(const char*);
	~Hamming8();
	friend ostream& operator<<(ostream&, const Hamming8&);
	friend istream& operator>>(istream&, Hamming8&);
	void get_p8();
	char* decode();
	unsigned short int get_error()const;
	void repair();
	void format_error(short int&)const;
	friend bool test_decode8();
	void change_bit(unsigned short int);
};