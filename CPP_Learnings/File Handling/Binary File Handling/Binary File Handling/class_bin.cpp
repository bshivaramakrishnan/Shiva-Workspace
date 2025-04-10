#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Student {
	int id;
	char name[50];  
	int age;
public:
	void input() {
		cout << "Student ID: ";
		cin >> id;
		cin.ignore();
		cout << "Enter the name for the student: ";
		cin.getline(name, 50); 
		cout << "Enter the age of the student: ";
		cin >> age;
	}

	void display() const {
		cout << "ID: " << id << "\nName: " << name << "\nAge: " << age << "\n";
	}
};

void writeToFile() {
	ofstream file("students.bin", ios::binary | ios::out);
	if (!file) {
		cout << "Error opening file for writing.\n";
		return;
	}
	int n;
	cout << "How many students? ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		Student s;
		cout << "Enter details for student " << i + 1 << ":\n";
		s.input();
		file.write(reinterpret_cast<char*>(&s), sizeof(s));
		

	}
	
	file.close();
}
void readFromFile() {
	ifstream file("students.bin", ios::binary | ios::in);
	if (!file) {
		cout << "Error opening file for reading.\n";
		return;
	}

	Student s;
	cout << "\nStudent Records:\n";
	while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
		s.display();
		cout << "----------------------\n";
	}

	file.close();
}
int main() {
	int choice;
	cout << "1. Write\n2. Read\nEnter your choice: ";
	cin >> choice;

	if (choice == 1) {
		writeToFile();
	}
	else if (choice == 2) {
		readFromFile();
	}
	else {
		cout << "Invalid choice\n";
	}

	return 0;
}



