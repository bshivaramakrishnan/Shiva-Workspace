/*
This programs Depicts default argument Constructor 
*/
#include<iostream>
using namespace std;
class base {
	int a, b, c;
public:
	base() {
		a = 10;
		b = 20;
		c = 30;
	}
	base(int x, int y = 15, int z = 100) :a(x),b(y),c(z){}

	void execute() {
		cout << "Default constructor called : " << a << " " << b << " " << c<<endl;
	}

};
void main() {
	base b1;
	base b2(100);
	base b3(20, 30);
	b1.execute();
	b2.execute();
	b3.execute();
}