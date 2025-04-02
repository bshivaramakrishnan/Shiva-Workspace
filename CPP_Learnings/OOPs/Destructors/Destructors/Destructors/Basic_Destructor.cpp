#include<iostream>
using namespace std;
class destructor {
	int a, b; 
public:

	destructor(int a, int b) {
		this->a = a;
		this->b = b;
		cout << "Constructor called : " << a<<" " << b<<endl;

			}
	~destructor() {
		cout << "Destructor Called";
	}

};
void main() {
	destructor(10, 20);

}