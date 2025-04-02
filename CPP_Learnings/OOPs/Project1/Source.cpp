#include<iostream>
using namespace std;
int multiply(int a, int b){
	return a * b;
}
int sub(int a, int b) {
	return a - b;
}

int add(int a, int b) {
	return a + b;

}
int main() {
	int a, b, c;
	cout << "Enter the numbers\n";
	cin >> a >> b;
	cout << "1:Addiiton \n 2:subtraction \n 3:multiply";
	cin >> c;
	switch (c)
	{
	default:
		break;
	case 1:
		cout << add(a, b);
		break;
	case 2:
		cout << sub(a, b);
		break;
	case 3:
		cout << multiply(a, b);

	}
	return 0;
}
