#include <iostream>
#include <fstream>

using namespace std;

void writeArrayToFile() {
    ofstream file("array.bin", ios::binary);
    if (!file) {
        cout << "Error creating file.\n";
        return;
    }

    int arr[10];
    cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; ++i) {
        cin >> arr[i];
    }

    file.write(reinterpret_cast<char*>(arr), sizeof(arr));
    file.close();
    cout << "Array written successfully.\n";
}

void updateIndex(int index, int newValue) {
    fstream file("array.bin", ios::in | ios::out | ios::binary);

    if (!file) {
        cout << "File couldn't be opened.\n";
        return;
    }

    
    file.seekp(index * sizeof(int), ios::beg);
    file.write(reinterpret_cast<char*>(&newValue), sizeof(int));

    file.close();
    cout << "Value at index " << index << " updated to " << newValue << ".\n";
}
void readArrayFromFile() {
    ifstream file("array.bin", ios::binary);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    int arr[10];
    file.read(reinterpret_cast<char*>(arr), sizeof(arr));

    cout << "Array values from file:\n";
    for (int i = 0; i < 10; ++i) {
        cout << "Index " << i << ": " << arr[i] << endl;
    }

    file.close();
}


int main() {
    int choice;
    do {
        cout << "\n1. Write Array\n2. Update Element\n3. Read Array\n4. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            writeArrayToFile();
        }
        else if (choice == 2) {
            int index, newValue;
            cout << "Enter index (0-9) to update: ";
            cin >> index;
            cout << "Enter new value: ";
            cin >> newValue;
            if (index >= 0 && index < 10)
                updateIndex(index, newValue);
            else
                cout << "Invalid index.\n";
        }
        else if (choice == 3) {
            readArrayFromFile();
        }
        else if (choice != 4) {
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
