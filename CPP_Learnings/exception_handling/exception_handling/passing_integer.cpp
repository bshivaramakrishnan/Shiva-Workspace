#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;
void main() {
	int x = -1;
	string error = " error message ";
	try {
		if (x < 0) {
			throw x;
		}
	}
	catch (int x) {
		cerr << "Error caught " <<x;
	}
}