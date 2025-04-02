//multilevel inhertiance
#include<iostream>
using namespace std;
class Base {
public:
	int a, b;
	Base(int x, int y) :a(x), b(y) {}
	void out() {
		cout << "A and B" << a << "\t" << b << endl;
	}
};
class Base2 :public Base {
public:
	int c, d;
	Base2(int x, int y, int x1, int y1) :Base(x, y), c(x1), d(y1) {}
	void out1() {
		cout << "C and D" << c << "\t" << d << endl;
	}

};
class child :public Base2
{
public:

	child(int x, int y, int x1, int y1) :Base2(x, y, x1, y1) {}


};
void main() {
	child c1(2, 3, 4, 5);
	c1.out();
	c1.out1();

}