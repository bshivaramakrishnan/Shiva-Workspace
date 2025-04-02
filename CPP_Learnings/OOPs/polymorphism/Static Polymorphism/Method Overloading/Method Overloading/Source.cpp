//method overloading
#include<iostream>
#include<math.h>
using namespace std;
void area(int s) {
	cout << "area of square: \t " << pow(s, 2)<<endl;
}
void area(int l, int b) {
	cout << "area of rectangle is : \t" << l * b<<endl;
}
void area(double r) {
	cout << "Area of Circle is : \t" << (22 / 7) * (pow(r, 2))<<endl;
}
void main() {
	cout << "Implementation of Static polymorphism : \t ";
	area(2.5);
	area(5);
	area(5, 10);
}