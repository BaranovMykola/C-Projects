#include <iostream>

using namespace std;

bool is_simple(unsigned int value)
{
	for (int i = 2;i < value;i++)
	{
		if ((value % i) == 0)
		{
			return false;
		}
	}
	return true;
}

bool divided_to_digit(unsigned int value)
{
	for (int i = 2;i < 10;++i)
	{
		if (value % i == 0)
		{
			return true;
		}
	}
	return false;
}

void main()
{
	
	for (int i = 9973; i > 2;--i)
	{
		if (!divided_to_digit(i))
		{
			cout << i << "\t" << boolalpha << is_simple(i) << endl;
		}
	}
	is_simple(121);
	system("pause");
}