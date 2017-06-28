#include "Hamming.h"


Hamming::Hamming(const unsigned short int _bin)
{
	get_code(get_p(_bin), _bin);
}

Hamming::Hamming(const char* _ch_bin):
	Hamming(_btoi(_ch_bin))
{
}


const bool* Hamming::get_p(const int bin)const
{
	bool* result = new bool[3];
	char _ch_bin[5];
	_itoa(bin, _ch_bin, 2);
	std::vector<int> partMatrix;
	for (int i = 0;i < 4;++i)
	{
		if (_ch_bin[i] == '1')
		{
			partMatrix.push_back(matrix[dataOrder[i+4-strlen(_ch_bin)]-1]); // [i+4-strlen(_ch_bin)] - in case lenght of _ch_bin < 4 gets correct columns | -1 - counting starts by 0, consts starts by 1.
		}
	}

	for (int i = 0;i < 3;++i)
	{
		int mult = 0;
		for (int j = 0;j < partMatrix.size();++j)
		{
			mult += partMatrix[j];
			partMatrix[j] = partMatrix[j] >> 1;
		}
		result[i] = mult % 2;
	}
	return result;
}

void Hamming::get_code(const bool* check, int data)
{
	code = 0;
	for (int i = 0;i < 2;++i)
	{
		code |= check[i] << 6 - i; // first 2 check-bites;
	}
	code |= data << 1;
	code &= _btoi("1110000");
	code |= check[2] << 3;
	data &= _btoi("0111");
	code |= data;
	delete[] check;

}

void Hamming::set_code(const unsigned short int _code)
{
	code = _code;
}

char* Hamming::decode() const
{
	unsigned short int result = _btoi("0000111") & code;
	unsigned short int _copy = code;
	_copy = _copy >> 4;
	_copy &= _btoi("1");
	_copy = _copy << 3;
	result |= _copy;
	char* _ch_bin = new char[5];
	_itoa(result, _ch_bin, 2);
	if (strlen(_ch_bin) < 4)
	{
		char* _extended_ch_bin = new char[5];
		_extended_ch_bin[0] = '\0';
		for (int i = 0;i < 4 - strlen(_ch_bin); ++i)
		{
			strcat(_extended_ch_bin, "0");
		}
		strcat(_extended_ch_bin, _ch_bin);
		delete[] _ch_bin;
		_ch_bin = _extended_ch_bin;
	}
	return _ch_bin;
}

void Hamming::repair()
{
	/*unsigned short int error = get_error();
	if (error != 0)
	{
		change_bit(error - 1);
	}*/
	short int error = get_error();
	if (error != 0)
	{
		format_error(error);
		change_bit(error);
	}
}

unsigned short int Hamming::get_error() const
{
	unsigned short int error = 0;
	char _ch_bin[9];
	_itoa(code, _ch_bin, 2);
	std::vector<int> partMatrix;
	for (int i = 0;i < 7;++i)
	{
		if (_ch_bin[i] == '1')
		{
			partMatrix.push_back(matrix[i+7-strlen(_ch_bin)]);
		}
	}
	while (partMatrix.size() > 1)
	{
		partMatrix[0] ^= partMatrix[partMatrix.size() - 1];
		partMatrix.pop_back();
	}
	error = partMatrix[0];
	return error;
}

void Hamming::change_bit(unsigned short int _index, const unsigned short int _k)
{
	if (_index > _k)
	{
		throw std::exception("Uncorrect bit");
	}
	unsigned short _copy = code >> _k - _index;
	bool bit = _copy % 2;
	if (!bit)
	{
		code |= 1 << _k - _index;
	}
	else
	{
		unsigned short int _change = INT_MAX - pow(2, _k - _index);
		code &= _change;
	}
}

void Hamming::format_error(short int& error) const
{
	--error;
}


Hamming::~Hamming()
{
}

istream & operator>>(istream& stream, Hamming& input)
{
	char data[5];
	stream >> data;
	int binary = _btoi(data);
	if (binary >= 16)
	{
		throw std::exception("Can't put more than four bites");
	}
	input.get_code(input.get_p(binary), binary);
	return stream;
}

ostream & operator<<(ostream& stream, const Hamming& output)
{
	char ch[9];
	_itoa(output.code, ch, 2);
	stream << std::setw(7) << std::setfill('0') << ch << std::endl;
	return stream;
}

unsigned int _btoi(const char* bin)
{
	int integer = 0;
	int index = 0;
	while (bin[index] != '\0')
	{
		++index;
	}
	for (int i = index;i >= 0;--i)
	{
		if (bin[i] == '1')
		{
			int add = 1;
			for (int j = 0;j < index - i - 1;++j)
			{
				add = add << 1;
			}
			integer |= add;
		}
	}
	return integer;
}


ostream & operator<<(ostream& stream, const Hamming8& output)
{
	char _ch_bin[9];
	_itoa(output.code, _ch_bin, 2);
	stream << std::setw(8) << std::setfill('0') << _ch_bin;
	return stream;

}

istream & operator>>(istream& stream, Hamming8& input)
{
	stream >> (Hamming&)input;
	input.get_p8();
	return stream;
}

Hamming8::Hamming8(const unsigned short int _code):
	Hamming(_code)
{
	get_p8();
}

Hamming8::Hamming8(const char* _ch_bin):
	Hamming(_ch_bin)
{
	get_p8();
}

Hamming8::~Hamming8()
{
}

void Hamming8::get_p8()
{
	unsigned short int _copy = code;
	unsigned short int mult = 0;
	bool even = false;
	for (int i = 0;i < 7;++i)
	{
		mult += _copy % 2;
		_copy = _copy >> 1;
	}
	even = mult % 2;
	code = code << 1;
	code |= even;
}

char* Hamming8::decode()
{
	unsigned short int _copy = code;
	code = code >> 1;
	char* result = Hamming::decode();
	code = _copy;
	return result;
}

unsigned short int Hamming8::get_error() const
{
	unsigned short int error = 0;
	char _ch_bin[9];
	_itoa(code, _ch_bin, 2);
	std::vector<int> partMatrix;
	for (int i = 0;i < 8;++i)
	{
		if (_ch_bin[i] == '1')
		{
			partMatrix.push_back(extendedMatrix[i + 8 - strlen(_ch_bin)]);
		}
	}
	while (partMatrix.size() > 1)
	{
		partMatrix[0] ^= partMatrix[partMatrix.size() - 1];
		partMatrix.pop_back();
	}
	error = partMatrix[0];
	return error;// 0 - any error | [1;7] e Z - two error | 8 - error in 7 bit | [9;15] - error int n-9 bit;
}

void Hamming8::repair()
{
	short int error = get_error();
	if (error < 8 && error != 0)
	{
		throw std::exception("Can't found two error");
	}
	format_error(error);
	change_bit(error);
}

void Hamming8::format_error(short int& _error) const
{
	_error -= 9;
	if (_error == -1)
	{
		_error = 7;
	}
}

void Hamming8::change_bit(unsigned short int _index)
{
	Hamming::change_bit(_index, 7);
}
