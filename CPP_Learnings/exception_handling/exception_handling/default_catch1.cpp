#include<iostream>
#include<stdexcept>
using namespace std;
void main() {
	int x = -1;
		try {
		if (x < 0) {
			throw x;
		}
	}
	catch (char* ch) {
		cout << "Character exception caught ";
	}
	catch (...) {
		cout << "default Exception Caught ";
	}
}