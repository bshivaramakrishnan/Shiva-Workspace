//imlpmentation of single inheritace 
#include<iostream>
using namespace std;
class base {
private:
	int a;
	int b;
	int c;
public:
	base(int x, int y, int z) :a(x), b(y), c(z) {}
	void add() {
		cout << "addition of A B C:\t" << a + b + c;
	}
};
class child :public base
{
public:
	child(int x, int y, int z) :base(x, y, z) {}
	void add1() {
		add();
	}
};
int main() {
	child c1(4, 5, 1);
	c1.add1();
	return 0;
}