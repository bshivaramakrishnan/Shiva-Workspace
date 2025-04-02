#include<iostream>
#include<string>
using namespace std;
class Base {
	string s;
public:
	Base(string s) {
		this->s = s;
	}
	void out()
	{
		cout << "The output of the function is : " << s;
	}
};

int main() {
	Base obj("Shiva");
	Base* ptr = &obj;
	void(Base:: * Methodptr)() = &Base::out;
	(ptr->*Methodptr)();

	return 0;
}