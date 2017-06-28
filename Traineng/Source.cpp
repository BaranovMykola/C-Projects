# include <iostream>
# include <fstream>
using namespace std;
template <typename T>
class Tree
{
	struct Link
	{
		Link* up;
		Link* right;
		Link* left;
		T value;
		Link(T _value, Link* _up=nullptr, Link* _right=nullptr, Link* _left=nullptr) :
			value(_value),
			right(_right),
			left(_left),
			right(_right)
		{
		}
		
	};
	Link* root;
public:
	Tree() :
		root(nullptr)
	{
	}
	void add(T obj)
	{
		Link* current=root;
		if (root.left == nullptr&&root.right==nullptr)
		{
			root = newLink(obj);
		}
		while (current != nullptr)
		{
			if (current->value > obj)
			{

				current = current->right;
			}
			else
			{
				current = currnt->left;
			}
		}
		current = new Link(T, )
	}
	~Tree()
	{

	}
};
class Point
{
	int x; int y;
public:
	Point(int _x, int _y):
		x(_x),
		y(_y)
	{
	}
};
template <typename T>
void sort_el_matrix(T** arr, int rows, int columns)
{
	if (rows < 1|| columns<1)
	{
		throw exception("size can't be negative");
	}
	if (rows != columns)
	{
		throw exception("matrix isnt square");
	}
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < rows;++j)
		{
			if (arr[i][i] < arr[j][j])
			{
				swap(arr[i][i], arr[j][j]);
			}
		}	
	}
	output(arr, rows, rows);
	cout << endl;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < rows;++j)
		{
			if (arr[i][rows - i-1] < arr[rows -i-1][i])
			{
				swap(arr[i][rows - i-1] , arr[rows -i-1][i]);
				cout << " a";
			}
		}
	}
	
}
template <typename T>
void output(T** arr, int rows, int columns)
{
	for (int i = 0; i < rows; ++i)
	{
		cout << endl;
		for (int j = 0; j < columns; ++j)
		{
			cout << arr[i][j] << " ";
		}
	}
}
void main()
{
	int size = 5;
	int** arr = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		arr[i] = new int[size];
	}
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			arr[i][j] = rand() % 4 +5;
		}
	}
	 output (arr, size, size);
	 cout << endl;
	 sort_el_matrix(arr, size, size);
	 output(arr, size, size);
	system("pause");
}