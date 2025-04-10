#include<iostream>
#include<fstream>
using namespace std;

struct student {
    char name[50];  
    int age;
    int id;
    int aggregate;
};

void writeToFile() {
    student s;

    cout << "Enter Student ID: ";
    cin >> s.id;
    cin.ignore();  

    cout << "Enter Student Name: ";
    cin.getline(s.name, 50); 

    cout << "Enter Student Age: ";
    cin >> s.age;

    cout << "Enter Total Marks: ";
    cin >> s.aggregate;

    ofstream file("student.bin", ios::binary | ios::app);  
    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();

    cout << "Record saved!\n";
}

void readFromFile() {
    student s;
    ifstream file("student.bin", ios::binary);

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        cout << "\nID: " << s.id
            << "\nName: " << s.name
            << "\nAge: " << s.age
            << "\nTotal Marks: " << s.aggregate << "\n";
        cout << "--------------------------\n";
    }

    file.close();
}

int main() {
    int choice;
    cout << "1. Write Student Record\n2. Read Student Records\nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
        writeToFile();
    else if (choice == 2)
        readFromFile();
    else
        cout << "Invalid choice.\n";

    return 0;
}
