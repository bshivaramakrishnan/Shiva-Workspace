#include<iostream>
#include<stdexcept>
 
using namespace std;
void main() {
	char s[] = "Hello";
	try {
		if (strcmp(s, "Hello")==0) {
			throw s;
		}
	}
	catch (char* s) {
		cout << "Character exception caught : " << s;
	}
}