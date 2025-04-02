#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main()
{
	struct student{
		double marks;
		int age;
		char name[10];
		};
	ofstream fileout("Binary1.bin", ios::binary);
	if (!fileout.is_open()) {
		cerr << "Error opening file ";
	}
	else {

	}
}