#include <iostream>
#include <fstream>
#include <string>
# include <exception>

using namespace std;
class MyExc:
	public exception
{
	int num;
	string message;
public:
	MyExc(int _num) :
		num(_num)		
	{
		if (num == 1)
		{
			message = "<0";
		}
		else
		{
			message = "head==nullptr";
		}
	}
	const char* what()

	{
		return message.c_str();
	}
};
class Queue
{
	struct Link
	{
		Link* next;
		Link* prev;
		int data;
		Link(int _data, Link* _prev=nullptr, Link* _next=nullptr) :
			next(_next),
			prev(_prev),
			data(_data)
		{
		}
		Link()
		{
		}
	};
	Link* head;
	Link* tail;
public:
	Queue ():
		head(nullptr),
		tail(nullptr)
	{ 
	}
	void add(int el)
	{
		if (el < 0)
		{
			throw MyExc(1);
		}
		if (tail == nullptr)
		{
			tail = new Link(el,head, tail);
			head = tail;
		}
		else
		{
			tail->next = new Link(el, tail, nullptr);
			tail = tail->next;

		}
	}
	int pop()
	{
		int res;
		Link* temp = head;
		if (head != tail)
		{
			res = temp->data;
			head = head->next;
			head->prev = nullptr;
			delete temp;
		}
		else if (head != nullptr)
		{
			res = head->data;
			delete head;
			head = nullptr;
			tail = nullptr;

		}
		else
		{
			throw MyExc(2);
		}
		return res;
	}

	friend ostream& operator<<(ostream& stream, const Queue& obj)
	{
		Link* temp = obj.head;
		while (temp != nullptr)
		{
			stream << temp->data << " -> ";
			temp = temp->next;
		}
		stream<<"/"<<endl;
		temp = obj.tail;
		stream << "reverse output" << endl;
		while (temp != nullptr)
		{
			stream << temp->data << " <- ";
			temp = temp->prev;
		}
		stream << "/" << endl;
		return stream;
	}
	~Queue()
	{
		while (head != nullptr)
		{
			pop();
		}
	}
	};



void main()
{
	_CrtMemState state1, state2, state3;
	_CrtMemCheckpoint(&state1);


	try
	{
		Queue a;
		for (int i = 0; i < 2; ++i)
		{
			a.add(i);
		}
		a.add(-5);
		cout << a;
		//a.pop();a.pop();a.pop();a.pop();
	}
	catch (char* exc)
	{
		cout << exc;
	}
	catch (MyExc exc)
	{
	cout<< exc.what();
	}
	catch (...)
	{
		cout << "erroooooooooooor!";
	}
	_CrtMemCheckpoint(&state2);
		if (_CrtMemDifference(&state3, &state2, &state1))
		{
			cout << "FF";
		}
	system("pause");
}