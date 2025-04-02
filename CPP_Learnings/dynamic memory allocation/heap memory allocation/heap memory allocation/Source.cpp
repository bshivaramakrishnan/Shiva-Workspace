#include<iostream>
using namespace std;
int main() {
	int a;
	cin >> a;
	int* ptr = new int(a);
	
	cout <<"\n"<< ptr << "\n";
	cout << *ptr;
	delete ptr;
	ptr = nullptr;
	return 0;
}