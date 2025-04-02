//runtime polymorphism acheived using virtual functions and pure virtual funtions

#include<iostream>
using namespace std;
class abstractclass {

public:
	virtual void calculate() = 0;
	virtual void sum(){
		cout << "Will be Overridden : ";
	}
};
class child:public abstractclass {
	int a, b;
public:
	child(int x, int y) :a(x), b(y) {};
	void calculate() override {
		cout << a *b<<endl;
	}
	void sum() override {
		cout << a + b;
	}
};
void main() {
	child c(10, 20);
	c.calculate();
	c.sum();

}