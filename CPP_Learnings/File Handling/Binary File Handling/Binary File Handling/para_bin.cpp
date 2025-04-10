#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void writetofile() {
    string para;
    string line;
    while (true) {
        getline(cin, line);
        if (line == "End" || line == "end") {
            break;
        }
        para += line + "\n";

    }
    ofstream file("paragraph.bin", ios::binary);
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }
    size_t length = para.size();
    file.write(reinterpret_cast<char*>(&length), sizeof(length));
    file.write(para.c_str(), length);
    file.close();
}
void readParagraph() {
    ifstream file("paragraph.bin", ios::binary);
    if (!file) {
        cout << "Error opening file for reading.\n";
        return;
    }

    size_t length;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));

    char* buffer = new char[length + 1];
    file.read(buffer, length);
    buffer[length] = '\0';

    string para(buffer);
    delete[] buffer;
    file.close();

    cout << "Paragraph read from file:\n";
    cout << para << endl;
}

int main() {
    int choice;
    cout << "1. Write Paragraph\n2. Read Paragraph\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
        writetofile();
    else if (choice == 2)
        readParagraph();
    else
        cout << "Invalid choice.\n";

    return 0;
}

