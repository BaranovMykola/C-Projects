#include "Relation.h"

void _Bin_matrix::_create_matrix()
{
	matrix = new bool*[height];
	for (int i = 0;i < height;++i)
	{
		matrix[i] = new bool[width];
		for (int j = 0;j < width;++j)
		{
			matrix[i][j] = false;
		}
	}
}

_Bin_matrix::_Bin_matrix(size_t _width, size_t _height):
	height(_height),
	width(_width)
{
	_create_matrix();
}

_Bin_matrix::_Bin_matrix(const _Bin_matrix& _Right):
	height(_Right.height),
	width(_Right.width)
{
	_create_matrix();
	for (int i = 0;i < height;++i)
	{
		for (int j = 0;j < width;++j)
		{
			(*this)[i][j] = _Right[i][j];
		}
	}
}

_Bin_matrix::~_Bin_matrix()
{
	for (int i = 0;i < height;++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

const bool* _Bin_matrix::operator[](int i) const
{
	return matrix[i];
}

bool * _Bin_matrix::operator[](int i)
{
	return matrix[i];
}

ostream & operator<<(ostream& stream, const _Bin_matrix& output)
{
	for (int i = 0;i < output.height;++i)
	{
		for (int j = 0;j < output.width;++j)
		{
			stream << output[i][j] << ' ';
		}
		stream << std::endl;
	}
	return stream;
}

istream & operator>>(istream& stream, _Bin_matrix& input)
{
	input._create_matrix();
	for (int i = 0;i < input.height;++i)
	{
		for (int j = 0;j < input.width;++j)
		{
			stream >> input[i][j];
		}
	}
	return stream;
}

_Bin_matrix::IteratorMatrix::IteratorMatrix(const _Bin_matrix& _Value):
	matrix(_Value.matrix),
	width(_Value.width),
	height(_Value.height),
	heightIndex(0),
	widthIndex(0)
{
}

_Bin_matrix::IteratorMatrix::IteratorMatrix(const IteratorMatrix& _Right):
	matrix(_Right.matrix),
	width(_Right.width),
	height(_Right.height),
	heightIndex(0),
	widthIndex(0)
{
}

const bool _Bin_matrix::IteratorMatrix::operator*() const
{
	return matrix[widthIndex][heightIndex];
}

bool & _Bin_matrix::IteratorMatrix::operator*()
{
	return matrix[widthIndex][heightIndex];
}

IteratorMatrix _Bin_matrix::IteratorMatrix::operator++()
{
	++widthIndex;
}
