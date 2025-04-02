#include<iostream>
using namespace std;
void main()
{
	int x = -1;
	try {
		if (x < 0) {
			throw x;
		}
	}
	catch (char& ch) {
		cout<< "Exception throw : Character  " << ch;
	}
	catch (int x) {
		cout << "integer exception thrown\t" << x;
	}
	catch (...) {
		cout << "default exeption thrown";
	}
}