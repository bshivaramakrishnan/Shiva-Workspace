#include<iostream>
using namespace std;
void main() {
	int a = 10;
	int* ptr = &a;
	cout << a<<endl;
	cout << ptr<< endl;
	cout << *ptr;
	//wild pointers 
	/*int* ptrw;
	ptrw = 20;*/

	//nullptr
	int* ptrn = nullptr;

	//dangling ptr
	int* ptrd = new int(5);
	delete ptrd;  
	cout << *ptrd;  

	//void ptr
	void* ptrv;
	int a = 10;
	ptrv = &a;
	cout << "Value: " << *(static_cast<int*>(ptrv)) << endl;
	

}