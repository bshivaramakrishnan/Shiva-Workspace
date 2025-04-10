#include<iostream>
#include<fstream>
#include<string>

using namespace std;
void write(fstream &obj) {
	string para;
	string line;
	while(true) {
		getline(cin, line);
		if (line == "END" || line == "end") {
			break;
		}
		else {
			para += "\n" + line;
		}
		obj << para;
	}
	
}
void read(fstream& obj) {
	string para;
	string line;
	while (getline(obj, line)) {
		cout << line << endl;
	}
	
}
void filestream() {
	string para;
	string line;
	fstream obj("text.txt", ios::in | ios::out | ios::app);
	if (!obj.is_open()) {
		cout << "Error While Opening File";
	}
	write(obj);
	obj.close();
	obj.open("text.txt", ios::in | ios::out | ios::app);

		read(obj);
		obj.close();
	}
	
	

void main() {
	filestream();
}