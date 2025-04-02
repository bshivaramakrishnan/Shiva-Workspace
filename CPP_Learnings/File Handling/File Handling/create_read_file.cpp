//Basic File Handling operations
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void main() {
	int o;

	cout << "Creating a file" << endl;
	ofstream fileobj("Test.txt");
	if (!fileobj.is_open()) {
		cout << "Error Creating File" << endl;
	}
	fileobj << "Entering line 1 " << endl;
	fileobj << "Data is being written into the file " << endl;
	fileobj << "The entered data is being successfully stored " << endl;
	fileobj.close();
	cout << "File has been successfully created in the current directory"<<endl;
	cout << "Enter 1 to open file :" << endl;
	cin >> o;
	if (o == 1) {
		ifstream obj("Test.txt");
		if (!obj.is_open()) {
			cout << "File Error while opening";
		}
		else {
			string line;
			while (getline(obj, line)) {
				cout << line << endl;
			}
		}obj.close();
	}
	ofstream obj1("File2");
	if (!obj1.is_open()) {
		cout << "Error while creating File";
	}
	else {
		obj1 << "Enter the details into file 2"<<endl;
		obj1 << "Entering sample data for the document "<<endl;
		obj1 << "Enter the details into file 2" << endl;
		obj1 << "Entering sample data for the document " << endl;
	}
	obj1.close();
	
}