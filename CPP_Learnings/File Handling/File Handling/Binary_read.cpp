#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ifstream fileread("binary.bin", ios::binary);
    if (!fileread.is_open()) {
        cout << "Error Opening file" << endl;
        return 1; // Exit with an error code
    }

    int num;
    fileread.read(reinterpret_cast<char*>(&num), sizeof(num));

    if (fileread.gcount() != sizeof(num)) { 
        cout << "Error reading from file" << endl;
        return 1;
    }

    cout << "Number read from file: " << num << endl;
    fileread.close();

    return 0; // Indicating successful execution
}
