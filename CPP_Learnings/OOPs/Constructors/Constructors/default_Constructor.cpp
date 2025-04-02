#include<iostream>
using namespace std;

class base 
{
	int a, b, c;
public:
	
	base() 
	{
		a = 10;
		b = 20;
		c = 30;
	}
	
	void execute() 
	{
		cout << "Default constructor called : " << a << " " << b << " " << c;
	}

};
void main() 
{
	base b1;
	b1.execute();
}