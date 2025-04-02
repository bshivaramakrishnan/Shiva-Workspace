#include<iostream>
#include<math.h>
using namespace std;
class Shape {
public:
	virtual void area() = 0;
	void display() {
		cout << "This is the area";
	}
};
class Circle :public Shape {
	double radius;
public:
	Circle(double r) :radius(r){}

	void area() override
	{
		cout << "Area of the circle initialised is : " << 3.14 * (pow(radius, 2));
	}
};
int main() {
	Circle c1(10);
	c1.area();
}