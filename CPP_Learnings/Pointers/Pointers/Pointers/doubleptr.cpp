#include<iostream>
using namespace std;
void main() {
	int a = 10;
	int* ptr = &a;
	int** dptr = &ptr;

	cout << **dptr << endl;
}
