#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class fileoperations {
public:
	void write() {
		string paragraph;
		string line;
		ofstream obj("Paragraph.txt");
		if (!obj.is_open()) {
			cout << "Error Creating File" << endl;
		}
		cout << "Enter the  paragraph and enter 'END' to stop writing" << endl;

		while (true) {
			getline(cin, line);
			if (line == "END") break;
			paragraph += line + "\n";
		}
		obj << paragraph;
		obj.close();
		cout << "File Saved" << endl;

	}
	void read() {
		string line;
		ifstream obj("Paragraph.txt");
		if (!obj.is_open()) {
			cout << "Error Opening File" << endl;
		}
		while (getline(obj, line)) {
			cout << line << endl;
		}
		obj.close();
	}
	void append() {
		string paragraph;
		string line;
		ofstream obj("Paragraph.txt", ios::app);
		if (!obj.is_open()) {
			cout << "Error Opening File" << endl;
		}
		while (true) {
			getline(cin, line);
			if (line == "END") {
				break;
			}
			paragraph += "\n" + line;

		}
		obj << paragraph;
		obj.close();
		cout << "File Appended" << endl;
	}
};
int menu(fileoperations& f) {
	int x;
	cout << "\tMenu" << endl;
	cout << "1: Create a File and Input Text" << endl;
	cout << "2: Output the Created File " << endl;
	cout << "3: Append to File " << endl;
	cout << "Enter your option :" << endl;
	cin >> x;
	switch (x) {
	case 1: {f.write(); break; }
	case 2: {f.read(); break; }
	case 3: {f.append(); break; }
	}
	return 0;

}
void main() {
	fileoperations f;
	menu(f);
	char o;
	while (true) {
		cout << "Select Y to Continue and N to Terminate the Program" << endl;
		cin >> o;
		if (o == 'Y' || o == 'y') {
			menu(f);
		}
		if (o == 'N' || o == 'n') {
			break;
		}

	}
}