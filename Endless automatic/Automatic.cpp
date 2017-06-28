#include "Automatic.h"


Automatic::State::State(unsigned int _quantity, bool _end):
	end(_end)
{
	for (int i = 0;i < _quantity;++i)
	{
		transition.push_back(0);
	}
}

istream & operator>>(istream& stream, Automatic::Transition& input)
{
	for (vector<unsigned int>::iterator i = input.set.begin(); i != input.set.end();++i)
	{
		stream >> *i;
	}
	return stream;
}

ostream & operator<<(ostream& stream, const Automatic::Transition& output)
{
	for (unsigned int i : output.set)
	{
		stream << i << " ";
	}
	return stream;
}

istream & operator>>(istream& stream, Automatic::State& input)
{
	for (int i = 0;i < input.transition.size();++i)
	{
		stream >> input.transition[i];
		stream >> i;
	}
	stream >> input.end;
	return stream;
}

ostream & operator<<(ostream& stream, const Automatic::State& output)
{
	for (unsigned int i : output.transition)
	{
		stream << i << " ";
	}
	stream << "\t" << std::boolalpha << output.end;
	return stream;
}

ostream & operator<<(ostream& stream, const Automatic& output)
{
	stream << "\t";
	for (char i : output.symbol)
	{
		stream << i << " ";
	}
	stream << std::endl;
	stream << std::setw(output.symbol.size() + 19) << std::setfill('-') << '-' << std::endl;
	for (pair<unsigned int, Automatic::State> i : output.data)
	{
		stream << i.first << "\t" << i.second << std::endl;
	}
	return stream;
}

istream & operator>>(istream& stream, Automatic& input)
{
	for (vector<char>::iterator i = input.symbol.begin(); i != input.symbol.end();++i)
	{
		stream >> *i;
	}
	for (map<unsigned int, Automatic::State>::iterator i = input.data.begin(); i != input.data.end(); ++i)
	{
		stream >> i->second;
	}
	return stream;
}

ostream & operator<<(ostream& stream, const OutAutomatic::Changes& output)
{
	for (char i : output.replace)
	{
		stream << i << " ";
	}
	return stream;
}

istream & operator>>(istream& stream, OutAutomatic::Changes& input)
{
	for (std::vector<char>::iterator i = input.replace.begin(); i != input.replace.end();++i)
	{
		stream >> *i;
	}
	return stream;
}

ostream & operator<<(ostream& stream, const OutAutomatic& output)
{
	stream << "\t";
	for (int j = 0;j < 2;++j)
	{
		for (char i : output.symbol)
		{
			stream << i << " ";
		}
		stream << "\t\t";
	}
	stream << std::endl;
	stream << std::setw(output.symbol.size() + 27) << std::setfill('-') << '-' << std::endl;
	unsigned int rows = 0;
	vector<OutAutomatic::Changes>::const_iterator j = output.out.begin();
	for (pair<unsigned int, Automatic::State> i : output.data)
	{
		stream << i.first << "\t" << i.second << " | " << *j++ << std::endl;
	}
	return stream;
}

istream & operator>>(istream& stream, OutAutomatic& input)
{
	for (vector<char>::iterator i = input.symbol.begin(); i != input.symbol.end();++i)
	{
		stream >> *i;
	}
	vector<OutAutomatic::Changes>::iterator j = input.out.begin();
	for (map<unsigned int, Automatic::State> ::iterator i = input.data.begin(); i != input.data.end();++i)
	{
		stream >> i->second >> *j++;
	}
	return stream;
}

unsigned int Automatic::find(const char _ch) const
{
	int i;
	for (i = 0;i < symbol.size();++i)
	{
		if (symbol[i] == _ch)
		{
			break;
		}
	}
	return i;
}

Automatic::Automatic(unsigned int _state_quantity, unsigned int _bit_automatic)
{
	if (_state_quantity == 0 || _bit_automatic == 0)
	{
		throw std::exception("Uncorrect automatic");
	}
	for (int i = 0;i < _bit_automatic;++i)
	{
		symbol.push_back('0');
	}
	for (int i = 0;i < _state_quantity;++i)
	{
		data.insert( pair<unsigned int, State>(i,State(_bit_automatic)) );
	}
}

Automatic::Automatic(map<unsigned int, State>& _state, vector<char>& _symbol):
	data(_state),
	symbol(_symbol)
{
}

bool Automatic::run(const char* word)const
{
	unsigned int current = 0;
	for (int i = 0;i < strlen(word);++i)
	{
		std::vector<unsigned int> transition = data.find(current)->second.transition;
		unsigned int _index = find(word[i]);
		if (_index >= transition.size())
		{
			throw std::exception("Error character in word");
		}
		current = transition[ _index ];
	}
	return data.find(current)->second.end;
}

OutAutomatic::Changes::Changes(unsigned int _size)
{
	for (int i = 0;i < _size;++i)
	{
		replace.push_back('0');
	}
}

OutAutomatic::OutAutomatic(unsigned int _state_quantity, unsigned int _bit_automatic):
	Automatic(_state_quantity, _bit_automatic)
{
	for (int i = 0;i < _state_quantity;++i)
	{
		out.push_back(_bit_automatic);
	}
}

OutAutomatic::OutAutomatic(map<unsigned int, State>& _states, vector<char>& _symbols, vector<Changes>& _output):
	Automatic(_states, _symbols),
	out(_output)
{
}

char * OutAutomatic::run(char* word)
{
	unsigned int _current_state = 0;
	unsigned int _new_state = 0;
	for (int i = 0;i < strlen(word);++i)
	{
		_new_state = data.find(_current_state)->second.transition[find(word[i])];
		word[i] = out[_current_state].replace[find(word[i])];
		_current_state = _new_state;
	}
	return word;
}

Automatic::Transition::Transition(unsigned int _quantity)
{
	for (int i = 0;i < _quantity;++i)
	{
		set.push_back(0);
	}
}
