#include <iostream>
#include <fstream>
#include <initializer_list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <deque>

int digits(int x)
{
	int result = 0;
	while(x > 0)
	{
		x /= 10;
		++result;
	}
	return result;
}

using namespace std;
void main()
{
	ostream_iterator<double> out(cout, " ");
	vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v2;
	vector<int> v3;
	vector<double> v4;

	copy(v.begin(), v.end(), out);
	cout << endl;

	transform(v.begin(), v.end(), back_inserter(v2), [](int i) { return i * 2; });

	copy(v2.begin(), v2.end(), out);
	cout << endl;
	int pos = 0;
	transform(v.begin(), v.end(), v2.begin(), back_inserter(v3), [&](int l, int r) { ++pos; return (l + r)*(pos % 2) + (l - r)*(pos % 2 - 1); });

	copy(v3.begin(), v3.end(), out);
	cout << endl;

	int t = 5;
	int d = 0;
	for_each(v.begin(), v.end(), [=](int &i) { if (i == t) i = d; });

	copy(v.begin(), v.end(), out);
	cout << endl;

	stable_sort(v3.begin(), v3.end(), [](int l, int r) { return digits(l) < digits(r); });

	copy(v3.begin(), v3.end(), out);
	cout << endl;

	double n = -1;
	double x = 0.1;
	generate_n(back_inserter(v4), 10, [&]() { ++n;return (pow(-1, n))*(pow(x, (2 * n + 1)) / (2 * n + 1)); });
	

	copy(v4.begin(), v4.end(), out);
	cout << endl;

	system("pause");
}