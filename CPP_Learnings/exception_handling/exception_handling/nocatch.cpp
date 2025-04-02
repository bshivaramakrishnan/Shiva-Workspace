#include<iostream>
#include<stdexcept>
using namespace std;
void main() {
	int x = 0;
	try {
		if (x == 0) {
			throw x;
		}
		else cout << "No Error";
	}
	catch (char* ch) {
		cout << "char Exception caught" << ch;
	}
}