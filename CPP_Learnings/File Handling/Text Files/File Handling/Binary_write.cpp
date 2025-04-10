#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main() {
	ofstream fileout("binary.bin", ios::binary);
	if (!fileout.is_open()) {
		cout << "Error Opening Binary File";
	}
	else {
		int num = 2932;
		fileout.write(reinterpret_cast<char*>(&num), sizeof(num));
		fileout.close();
		return 0;
	}
}