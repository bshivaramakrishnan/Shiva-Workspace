//implementation of encapsulation using Access modifiers with
#include<iostream>
using namespace std;
class Encapsulation {
public:
	Encapsulation(int x, int y, int z, int x1, int y1, int z1) :a(x), b(y), c(z), d(x1), e(y1), f(z1) {} //constructor
private:
	int a;
	int b;
	void privatefunc() {
		cout << "private addition\t" << a + b;
	}
	void privatefunc1() {
		cout << "a+b+c+d:\t" << a + b + c + d;

	}
	void privatefunc2() {
		cout << "a+b+c+d+e+f:\t" << a + b + c + d + e + f;

	}
protected:
	int c, d;
	void protectedfunc() {
		cout << "Protected addition\t" << c + d;
	}
	void potectedfunc1() {
		cout << "a+b+c+d:\t" << a + b + c + d;
	}
	void potectedfunc2() {
		cout << "a+b+c+d+e+f:\t" << a + b + c + d + e + f;
	}
public:
	int e, f;
	void publicfunc() {
		cout << "Protected addition\t" << e+ f;
		void privatefunc2();
	}
	void publicfunc1() {
		cout << "a+b+c+d:\t" << a + b + e + f;
		potectedfunc2();
	}
	void publicfunc2() {
		cout << "a+b+c+d+e+f:\t" << a + b + c + d + e + f;
	}
};
void main() {
	Encapsulation imp(1, 2, 3, 4, 5, 6);
	imp.publicfunc2();
	imp.publicfunc1();
	imp.publicfunc();
	imp.publicfunc2();
}