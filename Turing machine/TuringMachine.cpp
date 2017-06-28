#include "TuringMachine.h"

TuringMachine::TuringMachine(string _configuration):
	state(start_state)
{
	set_configuration(_configuration);
	capitulum = tape.begin();
}

TuringMachine::TuringMachine(map<_Key, _Value>& _Right):
	state(start_state),
	program(_Right)
{
}

void TuringMachine::set_configuration(string _configuration)
{
	tape.clear();
	for (char i : _configuration)
	{
		tape.push_back(i);
	}
	capitulum = tape.begin();
	state = start_state;
}

string TuringMachine::get_configuration() const
{
	string result("");
	for (char i : tape)
	{
		result.push_back(i);
	}
	return result;
}

void TuringMachine::set_program(map<_Key, _Value>& _Val)
{
	program = _Val;
}

void TuringMachine::set_program(std::pair<_Key, _Value> _Val)
{
	program.insert(_Val);
}

void TuringMachine::run()
{
	_Value exchange;
	do
	{
		exchange = program.find(_Key(state, *capitulum))->second;
		*capitulum = exchange.ch;
		state = exchange.state;
		if (exchange.action == MOVE::LEFT)
		{
			if (capitulum == tape.begin())
			{
				tape.push_front(empty);
			}
			--capitulum;
		}
		else if (exchange.action == MOVE::RIGHT)
		{
			list<char>::iterator copy = capitulum;
			if (++copy == tape.end())
			{
				tape.push_back(empty);
			}
			++capitulum;
		}
	}
	while (state != end_state);
}

istream& operator>>(istream& stream, _Key& input)
{
	stream >> input.state >> input.ch;
	return stream;
}

bool operator<(const _Key& _Left, const _Key& _Right)
{
	bool result;
	if (_Left.state != _Right.state)
	{
		result = (_Left.state < _Right.state);
	}
	else
	{
		result = (_Left.ch < _Right.ch);
	}
	return result;
}

bool operator==(const _Key& _Left, const _Key& _Right)
{
	return ((_Left.state == _Right.state) && (_Left.ch == _Right.ch));
}

istream & operator>>(istream& stream, _Value& input)
{
	short int _action;
	stream >> (_Key&)input >> _action;
	switch (_action)
	{
		case -1:	input.action = MOVE::LEFT;break;
		case 1:		input.action = MOVE::RIGHT;break;
		default:	input.action = MOVE::NONE;
	}
	return stream;
}
