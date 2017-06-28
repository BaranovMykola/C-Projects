#include <iostream>

using namespace std;

void printArray(const int *a, size_t n)
{
	for (int i = 0;i < n;i++)
	{
		cout << a[i] << " ";
	}
}//Just print array
int *add(int *a, size_t n, int add)
{
	int *result = new int[n + 1];
	for (int i = 0;i < n;i++)
	{
		result[i] = a[i];//First n elemnts will be same
	}
	result[n] = add;//+1 elemnts to new array
	delete[]a;
	return result;
}//Add new elemnt to array
int *removeE(int *a, size_t n)
{
	int *result = new int[n - 1];
	for (int i = 0;i < n - 1;i++)
	{
		result[i] = a[i];
	}
	delete[]a;
	return result;
}//Decreasing array
bool checkArray(int *a, size_t n, int element, bool s = false)
{
	if (s)
	{
		cout << endl << endl << "*******************************************" << endl << "I must find elemnt '" << element << "' in array: {";
		for (int i = 0;i < n;i++) cout << a[i] << ", ";
		cout << "} sizeR: " << n + 1 << endl << endl;
	}
	for (int i = 0;i < n + 1;i++)
	{
		cout << a[i] << " = " << element << " <-> " << boolalpha << !(a[i] == element) << endl;
		if (a[i] == element)
		{//If exists this elemnt in array
			if (s)		cout << "I've found something like this" << endl << "*******************************************" << endl;
			return false;
		}
	}
	if (s) cout << "I have'nt found anything seems" << endl << "*******************************************" << endl << endl;
	return true;
}//Check if exist smth in array
unsigned int getDiff(int *a, int*b, size_t n, size_t m)
{
	bool t = false;
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			if (a[i] == b[j])
			{
				t = true;
				break;
			}
		}
		if (!t) return a[i];
		t = false;
	}
	return 0;
}
int *combine(int *a, int*b, size_t n, size_t m)
{
	int *res = new int[m + n];
	for (int i = 0;i < n;++i)
	{
		res[i] = a[i];
	}
	int j = 0;
	for (int i = n;i < n + m + 1;++i)
	{
		res[i] = b[j++];
	}
	return res;
}
class graph
{
private:
	int **a, n;
public:
	graph() :a()
	{
		cout << "Enter count of vertexs:";
		cin >> n;
		cout << "Enter pairs of vertex (edge) or '0-0' to end typing edges:";
		int x, y;
		int **b = new int*[n];
		for (int i = 0;i < n;i++) b[i] = new int[n];
		for (int i = 0;i < n;i++)
		{
			for (int j = 0;j < n;j++)
			{
				b[i][j] = 0;
			}
		}
		do
		{
			cin >> x;
			cin >> y;
			cout << endl;
			x--;
			y--;
			if (x >= 0 && y >= 0) b[x][y] = b[y][x] = 1;
		} while (x >= 0 && y >= 0);
		a = b;
	}
	graph(int **aa, int nn) : a(aa), n(nn) {}
	void print()
	{
		cout << "   ";
		for (int i = 0;i < n;i++) cout << " " << i + 1 << " ";
		cout << endl << "   ";
		for (int i = 0;i < n;i++) cout << " _ ";
		cout << endl;
		for (int i = 0;i < n;i++)
		{
			cout << i + 1 << ":  ";
			for (int q = 0;q < n;q++)
			{
				cout << this->a[i][q] << "  ";
			}
			cout << endl;
		}
	}
	int *DFN(size_t &count, unsigned int vertex)
	{
		int *r = new int[1];
		int *steck = new int[1];
		size_t sizeR = 0, sizeSteck = 0;//Size of steck & result
		r[sizeR] = vertex;//First vertex
		steck[sizeSteck] = vertex;//First vertex in steck
		bool end = true;
		while (end)
		{
			cout << "Steck:\t"; printArray(steck, sizeSteck + 1);//Print out steck
			cout << endl;
			cout << "Vertexs:\t"; printArray(r, sizeR + 1);//Print out vertexs
			cout << endl;
			bool deleteSteck = false;//Variable of deleting last vertex from steck
			for (int i = 0;i < n;i++)
			{
				cout << "[CHECK]: a[r[" << sizeSteck << "]-1][i] = a[" << steck[sizeSteck] - 1 << "][" << i << "] = " << a[steck[sizeSteck] - 1][i] << " && "
					" checkArray(r, " << sizeR << ", " << i + 1 << ") <-> " << boolalpha << checkArray(r, sizeR, i + 1, true) << endl;//System information
				if (a[steck[sizeSteck] - 1][i] == 1 && checkArray(r, sizeR, i + 1))
				{//If DFN found vertex adjacent to lastest vertexs in steck && this vertex doesn't checked yet
					steck = add(steck, sizeSteck + 1, i + 1);//Add vertex to steck
					r = add(r, (sizeR + 1), (i + 1));//Add vertex to result
					cout << "[ADD]: Add vertex '" << i + 1 << "'" << endl << endl;//System information
					sizeR++;//Increasinf size of resoult
					sizeSteck++;//Increasing size of steck
					count++;
					deleteSteck = true;//Don't touch steck whil this iteartion
					break;//End for
				}
			}
			if (!deleteSteck)
			{//If DFN didn't find new vertex
				cout << "[REMOVE]: Remove lastest vertex from steck" << endl << endl;
				steck = removeE(steck, sizeSteck + 1);//Remove lastest vertxe from steck
				sizeSteck--;//Decreasing size of steck
				if (sizeSteck == -1)
				{//If size of steck == 0
					cout << "[END] Steck is empty. End of cycle" << endl;
					end = false;//End cycle
				}
			}
			deleteSteck = false;//Don't touch steck while iteration again
		}
		return r;//Return result

	}
	size_t getCountvertexs()
	{
		return n;
	}
};
void main()
{
	graph b;
	int currentvertex, *allvertexs = new int[b.getCountvertexs()], *realvertexs = new int[b.getCountvertexs()], *tempvertexs = new int[b.getCountvertexs()], result = 0;
	size_t countTempvertex = 1;//Count of vertexs which we'll get after DFN-method
	for (int i = 0;i < b.getCountvertexs();++i)
	{
		allvertexs[i] = i + 1;//Inicialization all vertexs
		realvertexs[i] = 0;//vertexs which we already checked
	}
	currentvertex = allvertexs[0];//First vertex
	for (int i = 0;i < b.getCountvertexs();++i)
	{
		countTempvertex = 1;
		++result;
		tempvertexs = b.DFN(countTempvertex, currentvertex);
		realvertexs = combine(tempvertexs, realvertexs, countTempvertex, b.getCountvertexs());
		currentvertex = getDiff(allvertexs, realvertexs, b.getCountvertexs(), b.getCountvertexs());
		if (currentvertex == 0)	break;
	}
	cout << endl << result << " component(s)" << endl;
	system("pause");
}