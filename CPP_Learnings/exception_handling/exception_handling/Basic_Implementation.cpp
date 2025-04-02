#include<iostream>
#include<stdexcept>

using namespace std;

void main() {
	int num, denom,rem;
	cout << "Enter numerator : ";
	cin >> num;
	cout << "enter denom : ";
	cin >> denom;
	try {
		if (denom == 0) {
			throw runtime_error("zero division error");
		}
		else rem = num / denom;
	}
	catch (const exception& e) {
		cerr << "Exception : " << e.what() << endl;
	}

}