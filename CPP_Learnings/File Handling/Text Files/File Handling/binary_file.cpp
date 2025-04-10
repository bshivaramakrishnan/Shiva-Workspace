#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    char name[50];
    int age;
    float marks;
};

void writeStudent() {
    ofstream file("students.dat", ios::binary | ios::app);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student s;
    cout << "Enter Student Name: ";
    cin.ignore();
    cin.getline(s.name, 50);
    cout << "Enter Age: ";
    cin >> s.age;
    cout << "Enter Marks: ";
    cin >> s.marks;

    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();
    cout << "Record written successfully!\n";
}

void readStudents() {
    ifstream file("students.dat", ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student s;
    cout << "\n--- Student Records ---\n";
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        cout << "Name: " << s.name << "\nAge: " << s.age << "\nMarks: " << s.marks << "\n\n";
    }
    file.close();
}

void updateStudent(int recordNum) {
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student s;
    file.seekp(recordNum * sizeof(Student), ios::beg);

    cout << "Enter New Name: ";
    cin.ignore();
    cin.getline(s.name, 50);
    cout << "Enter New Age: ";
    cin >> s.age;
    cout << "Enter New Marks: ";
    cin >> s.marks;

    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();
    cout << "Record updated successfully!\n";
}

void deleteStudent(int recordNum) {
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    if (!inFile || !outFile) {
        cout << "Error opening files!" << endl;
        return;
    }

    Student s;
    int currentRecord = 0;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (currentRecord != recordNum) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        }
        currentRecord++;
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    cout << "Record deleted successfully!\n";
}

int main() {
    int choice, recordNum;

    do {
        cout << "\n--- Binary File Handling ---\n";
        cout << "1. Write Student Record\n";
        cout << "2. Read Student Records\n";
        cout << "3. Update Student Record\n";
        cout << "4. Delete Student Record\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: writeStudent(); break;
        case 2: readStudents(); break;
        case 3:
            cout << "Enter Record Number to Update: ";
            cin >> recordNum;
            updateStudent(recordNum);
            break;
        case 4:
            cout << "Enter Record Number to Delete: ";
            cin >> recordNum;
            deleteStudent(recordNum);
            break;
        case 5: cout << "Exiting program...\n"; break;
        default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
