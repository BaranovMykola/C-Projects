#include "Sudoku.h"



Sudoku::Sudoku()
{
	field = new unsigned short int*[9];
	for (int i = 0;i < size;++i)
	{
		field[i] = new unsigned short int[9];
		for (int j = 0;j < size;++j)
		{
			field[i][j] = 0;
		}
	}
}


Sudoku::~Sudoku()
{
	for (int i = 0;i < size;++i)
	{
		delete[] field[i];
	}
	delete field;
}

void Sudoku::fill()
{
	srand(time(0));
	struct xy
	{
		unsigned short int i;
		unsigned short int j;
		int* option;
		int index;
		xy(unsigned short int _i, unsigned short int _j, int* _option, int _index) : i(_i), j(_j), option(_option), index(_index) {};
	};
	std::stack<xy> way;
	bool back = false;
	int* option;
	int index;
	for (int i = 0;i < size;++i)
	{
		if (back)
		{
			--i;
		}
		for (int j = 0;j < size;++j)
		{
			if (!back)
			{
				option = get_option();
				index = 0;
			}
			else
			{
				--j;
			}
			back = false;
			try
			{
				while (!(check_row(i) && check_colum(j) && check_square(i, j)) || field[i][j] == 0)
				{
					field[i][j] = option[index];
					if (index >= 9)
					{
						throw std::exception("Impossible");
					}
					++index;
				}
				way.push(xy(i, j, option, index));
			}
			catch (...)
			{
				field[i][j] = 0;
				i = way.top().i;
				j = way.top().j;
				field[i][j] = 0;
				index = way.top().index;
				option = way.top().option;
				way.pop();
				back = true;
			}
		}
	}
	while(!way.empty())
	{
		delete way.top().option;
		way.pop();
	}
}

bool Sudoku::check_row(unsigned short int r)
{
	bool error = false;
	for (int i = 0;i < size;++i)
	{
		for (int j = i+1;j < size;++j)
		{
			if (field[r][i] == field[r][j] && field[r][i] != 0)
			{
				error = true;
				break;
			}
		}
		if (error)
		{
			break;
		}
	}
	return !error;
}

bool Sudoku::check_colum(unsigned short int c)
{
	bool error = false;
	for (int i = 0;i < size;++i)
	{
		for (int j = i + 1;j < size;++j)
		{
			if (field[i][c] == field[j][c] && field[i][c] != 0)
			{
				error = true;
				break;
			}
		}
		if (error)
		{
			break;
		}
	}
	return !error;
}

bool Sudoku::check_square(unsigned short int i, unsigned short int j)
{
	bool error = false;
	vector<int> place;
	i -= i % 3;
	j -= j % 3;
	for (int i1 = i;i1 < i + 3;++i1)
	{
		for (int j1 = j; j1 < j + 3;++j1)
		{
			place.push_back(field[i1][j1]);
		}
	}
	for (int i1 = 0;i1 < size;++i1)
	{
		for (int j1 = 0;j1 < size;++j1)
		{
			if (place[i1] < place[j1])
			{
				std::swap(place[i1], place[j1]);
			}
		}
	}
	for (int i1 = 0;i1 < size-1;++i1)
	{
		if (place[i1] == place[i1 + 1] && place[i1] != 0)
		{
			error = true;
			break;
		}
	}
	return !error;
}

void Sudoku::set(unsigned short int i, unsigned short int j, unsigned short int _val)
{
	field[i][j] = _val;
}

int * Sudoku::get_option()
{
	srand(time(0));
	int* result = new int[size];
	for (int i = 0;i < size;++i)
	{
		result[i] = i+1;
	}
	for (int i = 0;i < rand() % 100;++i)
	{
		std::swap(result[rand() % 9], result[rand() % 9]);
	}
	return result;
}

ostream & operator<<(ostream& stream, const Sudoku& output)
{
	for (int i = 0;i < size;++i)
	{
		if (i % 3 == 0)
		{
			stream << std::setw(25) << std::setfill('-') << "-" << std::endl;
		}
		for (int j = 0;j < size;++j)
		{
			if (j % 3 == 0)
			{
				stream << '|' << ' ';
			}
			stream << output.field[i][j] << ' ';
		}
		stream << '|' << std::endl;
	}
	stream << std::setw(25) << std::setfill('-') << "-" << std::endl;
	return stream;
}
