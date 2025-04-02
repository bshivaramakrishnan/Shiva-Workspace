/*
Constructor Overloading using signature placement 
*/
#include<iostream>
#include<string>
using namespace std;
class base {
	int a;
	string b;
	double c;
public:
	base(int a, string b,double c) {
		this->a = a;
		this->b = b;
		this->c = c;
		cout << "Constructor 1 Called\t" << a << " \t" << b << "\t " << c << endl;
	}
	base(string b, int a, double c) {
		this->a = a;
		this->b = b;
		this->c = c;
		cout << "Constructor 2 Called\t" << a << "\t " << b << "\t " << c << endl;
	}
}; 
void main() {
	
	cout<< "Initialising Constructor (int,string,double)\t";
	base b1(8, "Shiva", 2.5);
	cout << "Initialising Constructor (string,int,double)\t";
	base b2("Shiva", 9, 5.5);

}

