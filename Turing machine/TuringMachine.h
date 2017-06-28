#pragma once
#include <fstream>
#include <string>
#include <list>
#include <map>

using std::string;
using std::istream;
using std::list;
using std::map;

const enum MOVE{LEFT, NONE, RIGHT};

const string start_state = "q1";
const string end_state = "q0";
const char empty = '|';

struct _Key
{
	string state;
	char ch;
	_Key(string _state = "", char _ch = '\0') :
		state(_state),
		ch(_ch)
	{
	}
	friend istream& operator>>(istream&, _Key&);
	friend bool operator<(const _Key&, const _Key&);
};

struct _Value : public _Key
{
	MOVE action;
	_Value(string _state = "", char _ch = '\0', MOVE _action = MOVE::NONE) :
		_Key(_state, _ch),
		action(_action)
	{
	}
	friend istream& operator>>(istream&, _Value&);
};

class TuringMachine
{
	list<char> tape;
	list<char>::iterator capitulum;
	string state;
	map<_Key, _Value> program;
public:
	TuringMachine(string = "");
	TuringMachine(map<_Key, _Value>&);
	void set_configuration(string = "");
	string get_configuration()const;
	void set_program(map<_Key, _Value>&);
	void set_program(std::pair<_Key, _Value>);
	void run();
};