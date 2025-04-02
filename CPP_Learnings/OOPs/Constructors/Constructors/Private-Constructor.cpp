#include<iostream>
using namespace std;

class SingletonClass
{
private:
	SingletonClass()
	{
		cout << endl << "private Execution" << endl;
	}

public:
	static SingletonClass getObject()
	{
		SingletonClass s;
		return s;
	}
	void print()
	{
		cout << endl << "public execution" << endl;
	}
};


int main()
{
	SingletonClass::getObject().print();
}