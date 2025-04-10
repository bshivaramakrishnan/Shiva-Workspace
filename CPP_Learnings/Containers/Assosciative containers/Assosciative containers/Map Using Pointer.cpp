#include <iostream>
#include <map>

using namespace std;

void insert(map<int, string*>& m, int key, const string& value) {
    if (m.find(key) != m.end()) {
        cout << "Key " << key << " already exists. Use modify option instead.\n";
    }
    else {
        m[key] = new string(value);
        cout << "Inserted key " << key << " with value: " << value << endl;
    }
}

void search(map<int, string*>& m, int key) {
    auto it = m.find(key);
    if (it != m.end()) {
        cout << "Found: Key = " << key << ", Value = " << *(it->second) << endl;
    }
    else {
        cout << "Key " << key << " not found!" << endl;
    }
}

void erase(map<int, string*>& m, int key) {
    auto it = m.find(key);
    if (it != m.end()) {
        delete it->second;
        m.erase(it);
        cout << "Deleted key " << key << " successfully.\n";
    }
    else {
        cout << "Key " << key << " not found!\n";
    }
}

void modify(map<int, string*>& m, int key, const string& newValue) {
    auto it = m.find(key);
    if (it != m.end()) {
        *(it->second) = newValue;
        cout << "Modified key " << key << " with new value: " << newValue << endl;
    }
    else {
        cout << "Key " << key << " not found! Use insert to add a new value.\n";
    }
}

void display(const map<int, string*>& m) {
    if (m.empty()) {
        cout << "The map is empty!\n";
        return;
    }
    cout << "\nCurrent Map Elements:\n";
    for (const auto& pair : m) {
        cout << "Key: " << pair.first << ", Value: " << *(pair.second) << endl;
    }
}

void checkKey(map<int, string*>& m, int key) {
    if (m.find(key) != m.end()) {
        cout << "Key " << key << " exists with value: " << *(m[key]) << endl;
    }
    else {
        cout << "Key " << key << " does not exist in the map.\n";
    }
}

void getSize(const map<int, string*>& m) {
    cout << "The map contains " << m.size() << " elements.\n";
}

void clearMap(map<int, string*>& m) {
    for (auto& pair : m) {
        delete pair.second;
    }
    m.clear();
    cout << "Map cleared successfully!\n";
}

void cleanup(map<int, string*>& m) {
    clearMap(m);
}

int main() {
    map<int, string*> m;
    int choice, key;
    string value;

    do {
        cout << "\nMap Operations:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Delete\n";
        cout << "4. Modify\n";
        cout << "5. Display\n";
        cout << "6. Check if Key Exists\n";
        cout << "7. Get Map Size\n";
        cout << "8. Clear Map\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> value;
            insert(m, key, value);
            break;
        case 2:
            cout << "Enter key to search: ";
            cin >> key;
            search(m, key);
            break;
        case 3:
            cout << "Enter key to delete: ";
            cin >> key;
            erase(m, key);
            break;
        case 4:
            cout << "Enter key to modify: ";
            cin >> key;
            cout << "Enter new value: ";
            cin >> value;
            modify(m, key, value);
            break;
        case 5:
            display(m);
            break;
        case 6:
            cout << "Enter key to check: ";
            cin >> key;
            checkKey(m, key);
            break;
        case 7:
            getSize(m);
            break;
        case 8:
            clearMap(m);
            break;
        case 9:
            cleanup(m);
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 9);

    return 0;
}
