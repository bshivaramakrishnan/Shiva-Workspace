#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writeToFile() {
    string name;
    cout << "Enter the file name to create file: ";
    cin >> name;

    int num;
    cout << "Enter the number: ";
    cin >> num;

    fstream obj(name + ".bin", ios::binary | ios::out);
    if (!obj.is_open()) {
        cout << "Error opening file for writing.\n";
        return;
    }

    obj.write(reinterpret_cast<char*>(&num), sizeof(num));
    obj.close();

    cout << "Number written successfully.\n";
}

void readFromFile() {
    string name;
    cout << "Enter file name to open: ";
    cin >> name;

    fstream fileread(name + ".bin", ios::binary | ios::in);
    if (!fileread.is_open()) {
        cout << "Error opening file.\n";
        return;
    }

    int num;
    fileread.read(reinterpret_cast<char*>(&num), sizeof(num));

    if (fileread.gcount() != sizeof(num)) {
        cout << "Error reading from file.\n";
        fileread.close();
        return;
    }

    cout << "Number read from file: " << num << endl;
    fileread.close();
}

int main() {  
    int choice;
    cout << "1. Write\n2. Read\nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
        writeToFile();
    else if (choice == 2)
        readFromFile();
    else
        cout << "Invalid choice.\n";

    return 0;
}
