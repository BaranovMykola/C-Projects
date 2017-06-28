#include <iostream>
#include <vector>

using namespace std;

// use: unsinged char; do not use: if, (?). Output 0,1,2,3,...,255

void print(vector<int> &a)
{
	for (auto i : a)
	{
		cout << i << ' ';
	}
}

void main()
{
	unsigned char _ch;
	_ch = 0;
	do
	{
		//cout << (int)_ch << endl;
	} while ((int)_ch++ < 255);

	vector<int> a (30, 0);
	for (auto i : a);
	print(a);
	system("pause");
}