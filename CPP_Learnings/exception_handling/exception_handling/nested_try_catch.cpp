#include<iostream>
#include<stdexcept>
using namespace std;
void main() {
	int x = -1;
	int y = 0;
	try {
		try {
			if (x < 0) {
				throw x;
			}
		}
		catch (int x) {
			cout << "Inner Try Block caught " << x << endl;
			throw y;
		}
	}
	catch (int y) {
		if (y > 1) {
			cout << "null";
		}
		else cout << "out catch block executed "<<y;
	}
}