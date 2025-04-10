#include<iostream>
#include<memory>

using namespace std;

int main() {
	shared_ptr<int> s = make_shared<int>();
	shared_ptr<int> s1 = s;
	int a = 10;
	*s = a;
	cout << *s1;


}