#include<iostream>
using namespace std;
class base {
	int a, b;
public:
	base(int x, int y) :a(x), b(y) {}
	int multiple() {
		return a * b;
	}
};
class child1 :public base {
	int a1, b1;
public:
	child1(int x, int y, int x1, int y1) :base(x, y), a1(x1), b1(y1) {}
	void sum1() {
		cout << a1 + b1 + multiple() << endl;
	}

};
class child2 :public base {
	int a2, b2;
public:
	child2(int x, int y, int x1, int y1) :base(x, y), a2(x1), b2(y1) {}
	void sum1() {
		cout << a2 + b2 + multiple() << endl;
	}

};
void main() {
	child1 c1(2, 3, 4, 5);
	cout << "\n";
	child2 c2(2, 3, 5, 6);
	c1.sum1();
	c2.sum1();

}