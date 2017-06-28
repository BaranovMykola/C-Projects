#pragma once
#include <iomanip>
#include <vector>
#include <fstream>
#include <map>

using std::map;
using std::istream;
using std::ostream;
using std::pair;
using std::vector;


class Automatic
{
public:
	struct Transition
	{
		vector<unsigned int> set;
		Transition(unsigned int=1);
		friend istream& operator>>(istream&, Transition&);
		friend ostream& operator<<(ostream&, const Transition&);

	};
	struct State
	{
		std::vector<unsigned int> transition;
		bool end;
		State(unsigned int = 2, bool = false);
		friend istream& operator>>(istream&, State&);
		friend ostream& operator<<(ostream&, const State&);
	};
protected:
	map<unsigned int, State> data;
	vector<char> symbol;
	unsigned int find(const char)const;
public:
	Automatic(unsigned int=1, unsigned int=2);
	Automatic(map<unsigned int, State>&, vector<char>&);
	bool run(const char*)const;
	friend ostream& operator<<(ostream&, const Automatic&);
	friend istream& operator>>(istream&, Automatic&);
};

class OutAutomatic : public Automatic
{
public:
	struct Changes
	{
		std::vector<char> replace;
		Changes(unsigned int=2);
		friend ostream& operator<<(ostream&, const Changes&);
		friend istream& operator>>(istream&, Changes&);
	};
private:
	std::vector<Changes> out;
public:
	OutAutomatic(unsigned int = 1, unsigned int = 2);
	OutAutomatic(map<unsigned int, State>&, vector<char>&, vector<Changes>&);
	char* run(char*);
	friend ostream& operator<<(ostream&, const OutAutomatic&);
	friend istream& operator>>(istream&, OutAutomatic&);
};