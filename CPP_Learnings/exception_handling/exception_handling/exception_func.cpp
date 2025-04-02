#include<iostream>
#include<stdexcept>

using namespace std;

void fun(int* ptr, int x) {
	if (x == 0) {
		throw x;
	}
	if (ptr == NULL) {
		throw ptr;
	}
	
}
int main() {
	try {
		fun(NULL, 0);
	}
	catch (int y) {
		cout << "integer exception caught " << y << endl;
	}
	catch (int *ptr1) {
		cout << "pointer exception caught " << ptr1 << endl;
	}
	
	return 0;
}